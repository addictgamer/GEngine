/* Please refer to license.txt */

#include "interface.hpp"

#include <iostream>

#include "../graphic/2d/2d.hpp"
#include "../graphic/window/window.hpp"

#include "../file/file.hpp"

namespace GEngine
{

namespace mui
{

Interface::Interface()
{
	//d2d = nullptr;
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
	//cegui_root_window = nullptr;
	//cegui_windowmanager = nullptr;
}

Interface::~Interface()
{
	/*if (d2d)
	{
		d2d = nullptr;
	}

	if (cegui_root_window)
	{
		delete cegui_root_window;
	}*/

	cegui_system = nullptr;
	cegui_resourceprovider = nullptr;
}

bool Interface::initialize(mgfx::d2d::D2D &d2d, std::vector<std::string> cegui_schemes)
{
	//d2d = &_d2d;
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

		sf::Vector2i coords = sf::Mouse::getPosition(*d2d.window->window2d);
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(coords.x, coords.y);

		//Map SFML Key and Mouse stuff to CEGUI stuff for injecting input into CEGUI.
		mapSFMLKeysToCEGUI();
		mapSFMLMouseToCEGUI();

		d2d.cegui_gui_context = &CEGUI::System::getSingleton().getDefaultGUIContext(); //Point this accordingly.
		d2d.cegui_renderer = &myRenderer;
		d2d.default_d2d = true;
	}
	catch(CEGUI::Exception& e)
	{
		std::cout << "CEGUI Exception:" << e.getMessage().c_str() << "\n";
		return false;
	}

	addD2D(d2d); //Add the D2D to the list of D2Ds.

	return true; //Success.
}

bool Interface::loadFont(std::string filepath)
{
	font.loadFromFile(filepath);

	return true;
}

void Interface::update()
{
	for (std::vector<mgfx::d2d::D2D* >::iterator iter = windows.begin(); iter != windows.end(); ++iter)
	//for (int i = 0; i < windows.size(); ++i)
	{
		(*iter)->window->setActive();
		if (windows.size() > 1)
		{
			//std::cout << "More than one & i = " << i << "\n";
			//std::cout << "More than 1.\n";
		}
		mgfx::d2d::D2D *d2d = *iter; //First point to this so I don't have to type crazy things every time.
		//mgfx::d2d::D2D *d2d = windows[i]; //First point to this so I don't have to type crazy things every time.
		CEGUI::GUIContext& context = *d2d->cegui_gui_context; //Next, point to this so that I don't have to type out the full thing every time.

		context.getMouseCursor().draw(); //Force draw it because it doesn't seem to want to work otherwise.

		//Now, handle injecting events into CEGUI.
		for (unsigned int i = 0; i < d2d->window->events.size(); ++i)
		{
			switch (d2d->window->events[i].type)
			{
			case sf::Event::KeyPressed:
				context.injectKeyDown(sfml_cegui_keymap[d2d->window->events[i].key.code]);
				break;
			case sf::Event::KeyReleased:
				context.injectKeyUp(sfml_cegui_keymap[d2d->window->events[i].key.code]);
				break;
			case sf::Event::TextEntered:
				context.injectChar(static_cast<char>(d2d->window->events[i].text.unicode));
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

		glBegin(GL_TRIANGLES);
			glVertex3f(  0.0f,  1.0f, 0.0f );
			glVertex3f( -1.0f, -1.0f, 0.0f );
			glVertex3f(  1.0f, -1.0f, 0.0f );
		glEnd( );
	}

	CEGUI::System::getSingleton().renderAllGUIContexts(); //Render all of CEGUI's stuffs.




	/*CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	//First, handle injecting events into CEGUI.
	for (unsigned int i = 0; i < d2d->window->events.size(); ++i)
	{
		switch (d2d->window->events[i].type)
		{
		case sf::Event::KeyPressed:
			context.injectKeyDown(sfml_cegui_keymap[d2d->window->events[i].key.code]);
			break;
		case sf::Event::KeyReleased:
			context.injectKeyUp(sfml_cegui_keymap[d2d->window->events[i].key.code]);
			break;
		case sf::Event::TextEntered:
			context.injectChar(static_cast<char>(d2d->window->events[i].text.unicode));
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

	CEGUI::System::getSingleton().renderAllGUIContexts(); //Render all of CEGUI's stuffs. //TODO: Make this work properly later.
	//CEGUI::System::getSingleton().getDefaultGUIContext().draw();
	//CEGUI::System::getSingleton().getDefaultGUIContext().getRenderTarget().draw();
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().draw(); //Force draw it because it doesn't seem to want to work otherwise.*/
}

CEGUI::Window* Interface::getRootWindow(mgfx::d2d::D2D &d2d)
{
	//return cegui_root_window;
	return d2d.getRootWindow();
}

void Interface::setRootWindow(CEGUI::Window *window, mgfx::d2d::D2D &d2d) //Sets the root window.
{
	/*cegui_root_window = window;
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(cegui_root_window);*/
	d2d.cegui_root_window = window;
	d2d.cegui_gui_context->setRootWindow(d2d.cegui_root_window);
}

CEGUI::Window* Interface::createVirtualWindowFromLayout(std::string layout/*, bool root*/)
{
	CEGUI::Window *window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layout);
	/*if (root) //If it's supposed to be the root window...
	{
		setRootWindow(window); //Set it.
	}*/

	return window;
}

void Interface::addD2D(mgfx::d2d::D2D &d2d)
{
	d2d.window->setActive();
	if (!d2d.cegui_renderer)
	{
		//When creating a renderer, perhaps force SFML to set the viewport to the d2d's window?
		d2d.cegui_renderer = &CEGUI::OpenGLRenderer::create();
	}

	if (!d2d.cegui_gui_context)
	{
		d2d.cegui_gui_context = &CEGUI::System::getSingleton().createGUIContext(d2d.cegui_renderer->getDefaultRenderTarget());
	}

	windows.push_back(&d2d);
}

} //namespace mui

} //namespace GEngine
