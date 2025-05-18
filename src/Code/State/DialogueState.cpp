#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <memory>

#include "DialogueState.h"
#include "Utility.hpp"
#include "EventQueue.h"
#include "Button.h"
#include "Label.h"
#include "NPC.h"

#include <iostream> 

DialogueState::DialogueState(StateStack& stack, Context context)
	: State(stack, context)
	, mGUIContainer()
{
	sf::Vector2f windowSize = context.window->getView().getSize();

    GameEvent event;
    if(context.event->pollEvent(event))
    {
        if (event.type == EventType::InteractWithNPC)
        {
            NPC* npc = static_cast<NPC*>(event.payload);
            auto mDialogues = npc->getDialogues();
            for (const auto& line : mDialogues)
            {
                std::wcout << line.toWideString() << std::endl;
            }
        }
    }
    
    auto mPausedText = std::make_shared<GUI::Label>("Game Paused", *context.fonts);
	mPausedText->getText().setCharacterSize(70);
	centerOrigin(mPausedText->getText());
    mPausedText->setPosition({0.5f * windowSize.x, 0.4f * windowSize.y});
    mPausedText->getText().setString("Game Paused");
	
    auto returnButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	returnButton->setPosition({0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75});
	returnButton->setText("Return");
	returnButton->setCallback([this] ()
	{
		requestStackPop();
	});

	auto backToMenuButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backToMenuButton->setPosition({0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125});
	backToMenuButton->setText("Back to menu");
	backToMenuButton->setCallback([this] ()
	{
		requestStateClear();
		requestStackPush(States::Menu);
	});

    mGUIContainer.pack(mPausedText);
	mGUIContainer.pack(returnButton);
	mGUIContainer.pack(backToMenuButton);
}

DialogueState::~DialogueState()
{
}

bool DialogueState::handleEvent(const sf::Event & event)
{
	mGUIContainer.handleEvent(event);
	return false;
}

bool DialogueState::update(sf::Time dt)
{
	return false;
}

void DialogueState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mGUIContainer);
}
