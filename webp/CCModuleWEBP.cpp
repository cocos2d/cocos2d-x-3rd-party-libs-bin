/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "platform/CCImage.h"
#include "base/CCModuleManager.h"
#include "decode.h"


using namespace cocos2d;

namespace
{
    bool WEBPModuleInitWithWEBPData(const unsigned char *data, ssize_t dataLen, DataFromModule &dataFromModule)
    {
        bool ret = false;
        
        do
        {
            WebPDecoderConfig config;
            if (WebPInitDecoderConfig(&config) == 0) break;
            if (WebPGetFeatures(static_cast<const uint8_t*>(data), dataLen, &config.input) != VP8_STATUS_OK) break;
            if (config.input.width == 0 || config.input.height == 0) break;
            
            
            dataFromModule.renderFormat = Texture2D::PixelFormat::RGBA8888;
            dataFromModule.width = config.input.width;
            dataFromModule.height = config.input.height;

            dataFromModule.dataLength = dataFromModule.width * dataFromModule.height * 4;
            dataFromModule.data = static_cast<unsigned char*>(malloc(dataFromModule.dataLength * sizeof(unsigned char)));
            
            config.output.u.RGBA.rgba = static_cast<uint8_t*>(dataFromModule.data);
            config.output.u.RGBA.stride = dataFromModule.width * 4;
            config.output.u.RGBA.size = dataFromModule.dataLength;
            config.output.is_external_memory = 1;
            
            if (WebPDecode(static_cast<const uint8_t*>(data), dataLen, &config) != VP8_STATUS_OK)
            {
                free(dataFromModule.data);
                dataFromModule.data = nullptr;
                break;
            }
            
            ret = true;
        } while (0);

        return ret;
    }


    class RegisterWEBP
    {
    public:
        RegisterWEBP()
        {
            static struct WEBPModule webpModule;
            webpModule.initWithWEBPData = WEBPModuleInitWithWEBPData;
            ModuleManager::registerModule("webp", &webpModule);
        }
    };

    static RegisterWEBP registerWEBP;

}

