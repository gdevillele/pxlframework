//
//  MenuSpriteUrl.cpp
//  pxlframework
//
//  Created by Gaëtan de Villèle on 5/19/14.
//
//


#include "MenuSpriteUrl.h"
//
//// C++
//#include <iostream>
//#include <fstream>
//// tools
//#include <fs.h>
//#include <system.h>
////
//#include "ScaleUtils.h"
//
//
//namespace px
//{
//	namespace engine
//	{
//		
//#pragma mark - static -
//		
//		MenuSpriteUrl* MenuSpriteUrl::newMenuSpriteUrl(const std::string& textureName,
//													   const Size contentSize,
//													   const RelativePosition relativePosition,
//													   const RelativePosition anchor,
//													   const Point& position,
//													   const std::string& url)
//		{
//			MenuSpriteUrl* result = new MenuSpriteUrl();
//			
//			result->setType(Sprite::Type::NOTEXTURE);
//			result->setContentSize(contentSize);
//			
//			result->setRelativePosition(relativePosition);
//			result->setAnchor(MenuSprite::convertRelativePositionIntoAnchorPoint(anchor));
//			result->setPosition(Point(position));
//			
//			MenuSprite* child = MenuSprite::newMenuSpriteWithTexture(textureName,
//																	 MenuSprite::RelativePosition::CENTER,
//																	 MenuSprite::RelativePosition::CENTER,
//																	 Point(0, 0));
//			result->addChild(child);
//			result->setMenuSprite(child);
//			
//			result->setUrl(url);
//			
//			result->sendRequest();
//			
//			return result;
//		}
//		
//		
//		
//#pragma mark - constructor / destructor -
//		
//		MenuSpriteUrl::MenuSpriteUrl() : MenuSprite(),
//		_url(),
//		_request(nullptr),
//		_menuSprite(nullptr)
//		{}
//		
//		
//		
//		MenuSpriteUrl::~MenuSpriteUrl()
//		{}
//		
//		
//		
//#pragma mark - public methods -
//		
//        // TODO: implementation
//		void MenuSpriteUrl::callbackSuccess(px::api::HttpRequest* request)
//		{
//            /*
//             size_t index = request->getRequestUrl().find_last_of("/");
//             std::string pictureName = request->getRequestUrl().substr(index+1);
//             std::string path = tools::fs::getDeviceTemporaryPath() + "fb_" + pictureName;
//             
//             std::ofstream image_file;
//             image_file.open (path, std::ios::out | std::ios::binary);
//             image_file.write(request->getResponseContent().c_str(), request->getResponseContent().size());
//             image_file.close();
//             
//             removeChild(_menuSprite);
//             
//             MenuSprite* downloaded = MenuSprite::newMenuSpriteWithTexture(path,
//             MenuSprite::RelativePosition::CENTER,
//             MenuSprite::RelativePosition::CENTER,
//             Point(0, 0));
//             // fb pictures are 50x50 pixels ... we display 200x200 points
//             downloaded->setScale((4.0f * ScaleUtils::pointToPixel()));
//             addChild(downloaded);
//             setMenuSprite(downloaded);
//             */
//		}
//		
//		
//		
//		void MenuSpriteUrl::callbackFailure(px::api::HttpRequest* request)
//		{
//			// nothing
//		}
//		
//		
//		
//#pragma mark - private methods -
//		
//		void MenuSpriteUrl::sendRequest()
//		{
//			px::api::Api::getInstance()->getUrl(_url,
//												this, functionPointerHttpCallback(MenuSpriteUrl::callbackSuccess),
//												this, functionPointerHttpCallback(MenuSpriteUrl::callbackFailure));
//		}
//		
//	}
//}




