/* Please refer to license.txt */

#include "interface.hpp"

#include <iostream>

#include "../graphic/2d/2d.hpp"
#include "../graphic/window/window.hpp"

#include "../file/file.hpp"

namespace mui
{

Interface::Interface()
{
	d2d = nullptr;
	cegui_system = nullptr;

	cegui_configfile_path = CEGUI_CONFIGFILE_PATH;
	cegui_logfile_path = CEGUI_LOGFILE_PATH;
	cegui_schemes_path = CEGUI_SCHEMES_PATH;
	cegui_imagesets_path = CEGUI_IMAGESETS_PATH;
	cegui_fonts_path = CEGUI_FONTS_PATH;
	cegui_layouts_path = CEGUI_LAYOUTS_PATH;
	cegui_looknfeels_path = CEGUI_LOOKNFEELS_PATH;
	cegui_luascripts_path = CEGUI_LUASCRIPTS_PATH;

	cegui_resourceprovider = nullptr;
	//cegui_windowmanager = nullptr;
}

Interface::~Interface()
{
	if (d2d)
	{
		d2d = nullptr;
	}

	cegui_system = nullptr;
	cegui_resourceprovider = nullptr;
}

bool Interface::initialize(mgfx::d2d::D2D &_d2d, std::vector<std::string> cegui_schemes, std::string gui_layout)
{
	d2d = &_d2d;

	//d2d->window->showMouseCursor(false); //CEGUI's default schemes are fugly with the mouse or don't have one at all. Using default sfml mouse. //TODO: Handle mouse.

	try
	{
		CEGUI::OpenGLRenderer& myRenderer = CEGUI::OpenGLRenderer::create();

		std::string log_directory("");
		mfile::FileManager::separatePathFromFilename(cegui_logfile_path, log_directory);
		//Check if the directory the cegui logfile is going to be kept in exists. It not, create it.
		if (!mfile::FileManager::directoryExists(log_directory))
		{
			mfile::FileManager::mkDir(log_directory);
		}

		CEGUI::System::create(myRenderer, nullptr, nullptr, nullptr, nullptr, cegui_configfile_path, cegui_logfile_path);

		//Initialise the required dirs for the CEGUI DefaultResourceProvider.
		cegui_resourceprovider = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
		cegui_resourceprovider->setResourceGroupDirectory("imagesets", cegui_imagesets_path);
		cegui_resourceprovider->setResourceGroupDirectory("fonts", cegui_fonts_path);
		cegui_resourceprovider->setResourceGroupDirectory("layouts", cegui_layouts_path);
		cegui_resourceprovider->setResourceGroupDirectory("looknfeels", cegui_looknfeels_path);
		cegui_resourceprovider->setResourceGroupDirectory("lua_scripts", cegui_luascripts_path);
		cegui_resourceprovider->setResourceGroupDirectory("schemes", cegui_schemes_path);
		//According to the documentation, this is only really needed if you are using Xerces and need to specify the schemas location.
		//cegui_resourceprovider->setResourceGroupDirectory("schemas", "datafiles/xml_schemas/");

		//Set the default resource groups to be used
		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		//This is only needed if the resourceprovider's schemas is set.
		//Setup default group for validation schemas.
		//CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
		//if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
		//{
		//	parser->setProperty("SchemaDefaultResourceGroup", "schemas");
		//}

		//Load the schemes specified in cegui_schemes.
		for (std::vector<std::string>::iterator i = cegui_schemes.begin(); i != cegui_schemes.end(); ++i) //TODO: Vector iterator.
		{
			CEGUI::SchemeManager::getSingleton().createFromFile(*i + ".scheme");
			loaded_schemes.push_back(*i); //Save it so we know how to access it later, if needed.
		}

		//TODO: Handle the mouse.
		/*CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("GlossySerpent/MouseArrow");
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();*/


		//CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("GlossySerpent/Tooltip"); //TODO: Set in XML, if possible.

		//Load all from the xml layout.
		CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(gui_layout); //TODO: Should this be saved somewhere, or can I just access it from CEGUI whenever I need, if I need to?
		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

		sf::Vector2i coords = sf::Mouse::getPosition(*d2d->window->window2d);
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(coords.x, coords.y);

		//Map SFML Key and Mouse stuff to CEGUI stuff for injecting input into CEGUI.
		mapSFMLKeysToCEGUI();
		mapSFMLMouseToCEGUI();
	}
	catch(CEGUI::Exception& e)
	{
		std::cout << "CEGUI Exception:" << e.getMessage().c_str() << "\n";
		return false;
	}

	return true; //Success.
}

bool Interface::loadFont(std::string filepath)
{
	font.loadFromFile(filepath);

	return true;
}

void Interface::update()
{
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	//First, handle injecting events into CEGUI.
	for (unsigned int i = 0; i < d2d->window->events.size(); ++i)
	{
		switch (d2d->window->events[i].type)
		{
		case sf::Event::KeyPressed:
			std::cout << "Injecting: \"" << d2d->window->events[i].text.unicode << "\" into CEGUI KeyPressed.\n";
			context.injectChar(d2d->window->events[i].text.unicode);
			context.injectKeyDown(sfml_cegui_keymap[d2d->window->events[i].key.code]);
			break;
		case sf::Event::KeyReleased:
			context.injectKeyUp(sfml_cegui_keymap[d2d->window->events[i].key.code]);
		 	break;
		case sf::Event::MouseMoved:
			{
				sf::Vector2i coords = sf::Mouse::getPosition(*d2d->window->window2d);
				context.injectMousePosition(coords.x, coords.y);
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				context.injectMouseButtonDown(CEGUI::LeftButton);
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				context.injectMouseButtonDown(CEGUI::MiddleButton);
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				context.injectMouseButtonDown(CEGUI::RightButton);
			}
			break;
		case sf::Event::MouseButtonReleased:
			switch (d2d->window->events[i].mouseButton.button)
			{
			case sf::Mouse::Left:
				context.injectMouseButtonUp(CEGUI::LeftButton);
				break;
			case sf::Mouse::Middle:
				context.injectMouseButtonUp(CEGUI::MiddleButton);
				break;
			case sf::Mouse::Right:
				context.injectMouseButtonUp(CEGUI::RightButton);
				break;
			}
			break;
		case sf::Event::MouseWheelMoved:
			context.injectMouseWheelChange(d2d->window->events[i].mouseWheel.delta);
			break;
		default:
			break;
		}
	}

	//onMouseButtonUp //Use this to check if the frame window's button was pressed.

	CEGUI::System::getSingleton().renderAllGUIContexts(); //Render all of CEGUI's stuffs.
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().draw(); //Force draw it because it doesn't seem to want to work otherwise.
}

} //namespace mui
