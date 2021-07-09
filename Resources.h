#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Resources
{
public:
	///<summary>Enum para las distintas imagenes del juego</summary>
	enum TextureId : int {
		Menu,
        EscenarioPelea,
		BotonPiedra,
		BotonPapel,
        BotonTijeras,
		Objeto,
	};

    
	enum FontId : int {
		RETRO,
		RETROSM
	};

	struct ImageInfo {
		TextureId textureId;
		string filename;
	};


	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};


	static vector<ImageInfo> imageRoutes;



};