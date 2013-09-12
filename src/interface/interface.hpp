/* Please refer to license.txt */

#pragma once

#undef interface // For some reason, the Win32 API defined 'interface' as 'struct'... *sigh*

#include <string>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>

#include <SFML/Graphics.hpp>

namespace mgfx
{

namespace d2d
{

class D2D;
class Sprite;

} //namespace d2d

class Window;

} //namespace mgfx

namespace mui
{

//These define the standard values for the corresponding variables in the Interface class.
#define CEGUI_CONFIGFILE_PATH "data/interface/cegui/cegui_config.xml"
#define CEGUI_LOGFILE_PATH "log/cegui.log"
#define CEGUI_FONTS_PATH "data/interface/cegui/fonts/"
#define CEGUI_IMAGESETS_PATH "data/interface/cegui/imagesets/"
#define CEGUI_LAYOUTS_PATH "data/interface/cegui/layouts/"
#define CEGUI_LOOKNFEELS_PATH "data/interface/cegui/looknfeels/"
#define CEGUI_LUASCRIPTS_PATH "data/interface/cegui/luascripts/"
#define CEGUI_SCHEMES_PATH "data/interface/cegui/schemes/"

class Interface
{
private:
	CEGUI::System* cegui_system;

	sf::Font font;

	sf::Text mString; //TODO: FOR TESTING.

	//CEGUI filepath stuff.
	//Default values are the corresponding #define at the beginning of this file.
	std::string cegui_configfile_path;
	std::string cegui_logfile_path;
	std::string cegui_schemes_path;
	std::string cegui_imagesets_path;
	std::string cegui_fonts_path;
	std::string cegui_layouts_path;
	std::string cegui_looknfeels_path;
	std::string cegui_luascripts_path;

	CEGUI::DefaultResourceProvider* cegui_resourceprovider; //The cegui resource provider.

	//CEGUI::WindowManager* cegui_windowmanager; //The cegui window manager. //Nah, just use: CEGUI::WindowManager::getSingleton()

	std::vector<std::string> loaded_schemes; //The loaded cegui schemes. I don't think this has much actual use, but we'll see.
public:
	mgfx::d2d::D2D *d2d;

	Interface();
	~Interface();

	/*
	 * Initializes the interface & CEGUI.
	 * Parameters:
	 *	&_d2d		:	reference to the 2d manager that this GUI belongs to.
	 *	cegui_shemes	:	vector containing the NAMES of all the cegui scheme files we're using. Example: "TaharezLook", note: NOT "TaharezLook.scheme". Do NOT include the file extension, only the actual name of the theme.
	 *	gui_layout	:	Name of the xml file that defines the program's GUI layout. Include file extension, in contrast to cegui_schemes. Leave blank ("") if you want to specify your GUI in the code rather than in an xml file.
	 */
	bool initialize(mgfx::d2d::D2D &_d2d, std::vector<std::string> cegui_schemes, std::string gui_layout);

	/*
	More of a draw update, since all it does (currently) is render all of cegui's stuffs.
	*/
	void update();

	//Loads a font.
	bool loadFont(std::string filepath);

	/*
	 * Hides the mouse (regardless of whether the current active mouse belongs to CEGUI or SFML).
	 */
	void hideMouse(); //TODO: Implement.

	/*
	 * Switches between the SFML mouse and the CEGUI mouse.
	 */
	void switchMouse(); //TODO: Implemenet.
};

} //namespace mui
