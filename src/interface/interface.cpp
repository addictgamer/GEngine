/* Please refer to license.txt */

#include "interface.hpp"

#include <iostream>

#include "../graphic/2d/2d.hpp"
#include "../graphic/window/window.hpp"

#include "../misc/time.hpp"

#include "../file/file.hpp"

namespace GEngine
{

namespace mui
{

Interface::Interface() : timer(mmisc::mtime::Timer::create())
{
	//timer = new mmisc::mtime::Timer;
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

		timer.start();
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
	float time_elapsed = ((float)timer.millisecondsElapsed() / (float)1000);
	//float time_elapsed = ((float)timer.millisecondsElapsed());

	unhandled_events.clear(); //Empty the unhandled events vector.

	for (std::vector<mgfx::d2d::D2D* >::iterator iter = windows.begin(); iter != windows.end(); ++iter)
	{
		(*iter)->window->setActive();

		mgfx::d2d::D2D *d2d = *iter; //First point to this so I don't have to type crazy things every time.
		//mgfx::d2d::D2D *d2d = windows[i]; //First point to this so I don't have to type crazy things every time.
		CEGUI::GUIContext& context = *d2d->cegui_gui_context; //Next, point to this so that I don't have to type out the full thing every time.

		//context.setMouseButtonMultiClickTimeout(0.1);
		//context.setMouseClickEventGenerationEnabled(false);

		context.injectTimePulse(time_elapsed);

		//std::cout << "Context size: " << context.getSurfaceSize() << "\n";

		context.getMouseCursor().draw(); //Force draw it because it doesn't seem to want to work otherwise.

		//Now, handle injecting events into CEGUI.
		for (unsigned int i = 0; i < d2d->window->events.size(); ++i)
		{
			switch (d2d->window->events[i].type)
			{
			case sf::Event::KeyPressed:
				if (!context.injectKeyDown(sfml_cegui_keymap[d2d->window->events[i].key.code]))
				{
					addUnhandledEvent(d2d->window->events[i], *d2d->window);
				}
				break;
			case sf::Event::KeyReleased:
				if (!context.injectKeyUp(sfml_cegui_keymap[d2d->window->events[i].key.code]))
				{
					addUnhandledEvent(d2d->window->events[i], *d2d->window);
				}
				break;
			case sf::Event::TextEntered:
				if (!context.injectChar(static_cast<char>(d2d->window->events[i].text.unicode)))
				{
					addUnhandledEvent(d2d->window->events[i], *d2d->window);
				}
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
					if(!context.injectMouseButtonDown(CEGUI::LeftButton))
					{
						addUnhandledEvent(d2d->window->events[i], *d2d->window);
						std::cout << "mouse button down not received by cegui\n";
					}
					else
					{
						std::cout << "mouse button down received by cegui\n";
					}
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
				{
					if(!context.injectMouseButtonDown(CEGUI::MiddleButton))
					{
						addUnhandledEvent(d2d->window->events[i], *d2d->window);
					}
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					if(!context.injectMouseButtonDown(CEGUI::RightButton))
					{
						addUnhandledEvent(d2d->window->events[i], *d2d->window);
					}
				}
				break;
			case sf::Event::MouseButtonReleased:
				switch (d2d->window->events[i].mouseButton.button)
				{
				case sf::Mouse::Left:
					if(!context.injectMouseButtonUp(CEGUI::LeftButton))
					{
						addUnhandledEvent(d2d->window->events[i], *d2d->window);
						std::cout << "mouse button up not received by cegui\n";
					}
					else
					{
						std::cout << "mouse button up received by cegui\n";
					}
					break;
				case sf::Mouse::Middle:
					if(!context.injectMouseButtonUp(CEGUI::MiddleButton))
					{
						addUnhandledEvent(d2d->window->events[i], *d2d->window);
					}
					break;
				case sf::Mouse::Right:
					if(!context.injectMouseButtonUp(CEGUI::RightButton))
					{
						addUnhandledEvent(d2d->window->events[i], *d2d->window);
					}
					break;
				}
				break;
			case sf::Event::MouseWheelMoved:
				if(!context.injectMouseWheelChange(d2d->window->events[i].mouseWheel.delta))
				{
					addUnhandledEvent(d2d->window->events[i], *d2d->window);
				}
				break;
			default:
				break;
			}
		}

		/*glBegin(GL_TRIANGLES);
			glVertex3f(  0.0f,  1.0f, 0.0f );
			glVertex3f( -1.0f, -1.0f, 0.0f );
			glVertex3f(  1.0f, -1.0f, 0.0f );
		glEnd( );*/

		//TODO: gui context draw() ?
		d2d->cegui_renderer->beginRendering();
		context.draw();
		d2d->cegui_renderer->endRendering();

		//std::cout << "Context multiclick timeout: " << context.getMouseButtonMultiClickTimeout() << "\n";
		//std::cout << "Context multiclick timeout: " << context.getMouseButtonMultiClickTolerance() << "\n";
	}

	//CEGUI::System::getSingleton().renderAllGUIContexts(); //Render all of CEGUI's stuffs.
	//TODO: Maybe the problem is the resource browser window doesn't have a root window set? Hmm...
	//I need to:
	//	* Post on the forums asking about how to render one context at a time.
	//	* And/or post on the forums asking about how to render to multiple SFML windows.
	CEGUI::System::getSingleton().injectTimePulse(time_elapsed);
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
	//TODO: gui context setRenderTarget (RenderTarget &target) ?
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

void Interface::addUnhandledEvent(sf::Event& event, mgfx::Window& window)
{
	unhandledEvent unhandled_event(window, event);
	unhandled_events.push_back(unhandled_event);
}

} //namespace mui

} //namespace GEngine
