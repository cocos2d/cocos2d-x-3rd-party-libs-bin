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

#include <string.h>
#include "platform/CCImage.h"
#include "tiffio.h"
#include "base/CCModuleManager.h"

using namespace cocos2d;

namespace
{
    typedef struct
    {
        const unsigned char * data;
        ssize_t size;
        int offset;
    }tImageSource;
    
    static tmsize_t tiffReadProc(thandle_t fd, void* buf, tmsize_t size)
    {
        tImageSource* isource = (tImageSource*)fd;
        uint8* ma;
        uint64 mb;
        unsigned long n;
        unsigned long o;
        tmsize_t p;
        ma=(uint8*)buf;
        mb=size;
        p=0;
        while (mb>0)
        {
            n=0x80000000UL;
            if ((uint64)n>mb)
                n=(unsigned long)mb;
            
            
            if((int)(isource->offset + n) <= isource->size)
            {
                memcpy(ma, isource->data+isource->offset, n);
                isource->offset += n;
                o = n;
            }
            else
            {
                return 0;
            }
            
            ma+=o;
            mb-=o;
            p+=o;
            if (o!=n)
            {
                break;
            }
        }
        return p;
    }
    
    static tmsize_t tiffWriteProc(thandle_t fd, void* buf, tmsize_t size)
    {
        CC_UNUSED_PARAM(fd);
        CC_UNUSED_PARAM(buf);
        CC_UNUSED_PARAM(size);
        return 0;
    }
    
    
    static uint64 tiffSeekProc(thandle_t fd, uint64 off, int whence)
    {
        tImageSource* isource = (tImageSource*)fd;
        uint64 ret = -1;
        do
        {
            if (whence == SEEK_SET)
            {
                CC_BREAK_IF(off >= (uint64)isource->size);
                ret = isource->offset = (uint32)off;
            }
            else if (whence == SEEK_CUR)
            {
                CC_BREAK_IF(isource->offset + off >= (uint64)isource->size);
                ret = isource->offset += (uint32)off;
            }
            else if (whence == SEEK_END)
            {
                CC_BREAK_IF(off >= (uint64)isource->size);
                ret = isource->offset = (uint32)(isource->size-1 - off);
            }
            else
            {
                CC_BREAK_IF(off >= (uint64)isource->size);
                ret = isource->offset = (uint32)off;
            }
        } while (0);
        
        return ret;
    }
    
    static uint64 tiffSizeProc(thandle_t fd)
    {
        tImageSource* pImageSrc = (tImageSource*)fd;
        return pImageSrc->size;
    }
    
    static int tiffCloseProc(thandle_t fd)
    {
        CC_UNUSED_PARAM(fd);
        return 0;
    }
    
    static int tiffMapProc(thandle_t fd, void** pbase, toff_t* psize)
    {
        return 0;
    }
    
    static void tiffUnmapProc(thandle_t fd, void* base, toff_t size)
    {
    }
    
    bool TIFFModuleInitWithTIFFData(const unsigned char *data, ssize_t dataLen, DataFromModule& dataInitFromTIFF)
    {
        bool ret = false;
        do
        {
            // set the read call back function
            tImageSource imageSource;
            imageSource.data    = data;
            imageSource.size    = dataLen;
            imageSource.offset  = 0;
            
            TIFF* tif = TIFFClientOpen("file.tif", "r", (thandle_t)&imageSource,
                                       tiffReadProc, tiffWriteProc,
                                       tiffSeekProc, tiffCloseProc, tiffSizeProc,
                                       tiffMapProc,
                                       tiffUnmapProc);
            
            if(nullptr == tif) break;
            
            uint32 w = 0, h = 0;
            uint16 bitsPerSample = 0, samplePerPixel = 0, planarConfig = 0;
            size_t npixels = 0;
            
            TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
            TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
            TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bitsPerSample);
            TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &samplePerPixel);
            TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &planarConfig);
            
            npixels = w * h;
            
            dataInitFromTIFF.renderFormat = Texture2D::PixelFormat::RGBA8888;
            dataInitFromTIFF.width = w;
            dataInitFromTIFF.height = h;
            
            dataInitFromTIFF.dataLength = npixels * sizeof (uint32);
            dataInitFromTIFF.data = static_cast<unsigned char*>(malloc(dataInitFromTIFF.dataLength * sizeof(unsigned char)));
            
            uint32* raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
            if (raster != nullptr)
            {
                if (TIFFReadRGBAImageOriented(tif, w, h, raster, ORIENTATION_TOPLEFT, 0))
                {
                    /* the raster data is pre-multiplied by the alpha component
                     after invoking TIFFReadRGBAImageOriented*/
//                    _preMulti = true;
                    
                    memcpy(dataInitFromTIFF.data, raster, npixels*sizeof (uint32));
                }
                
                _TIFFfree(raster);
            }
            
            
            TIFFClose(tif);
            
            ret = true;
        } while (0);
        
        return ret;
    }
    
    class RegisterTIFF
    {
    public:
        RegisterTIFF()
        {
            static struct TIFFModule tiffModule;
            tiffModule.initWithTIFFData = TIFFModuleInitWithTIFFData;
            ModuleManager::registerModule("tiff", &tiffModule);
        }
    };
    
    static RegisterTIFF registerTIFF;
}

