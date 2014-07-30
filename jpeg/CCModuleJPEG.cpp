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
#include <setjmp.h>
#include "platform/CCImage.h"
#include "base/CCModuleManager.h"
#include "jpeglib.h"


using namespace cocos2d;

namespace
{
    /*
     * ERROR HANDLING:
     *
     * The JPEG library's standard error handler (jerror.c) is divided into
     * several "methods" which you can override individually.  This lets you
     * adjust the behavior without duplicating a lot of code, which you might
     * have to update with each future release.
     *
     * We override the "error_exit" method so that control is returned to the
     * library's caller when a fatal error occurs, rather than calling exit()
     * as the standard error_exit method does.
     *
     * We use C's setjmp/longjmp facility to return control.  This means that the
     * routine which calls the JPEG library must first execute a setjmp() call to
     * establish the return point.  We want the replacement error_exit to do a
     * longjmp().  But we need to make the setjmp buffer accessible to the
     * error_exit routine.  To do this, we make a private extension of the
     * standard JPEG error handler object.  (If we were using C++, we'd say we
     * were making a subclass of the regular error handler.)
     *
     * Here's the extended error handler struct:
     */
    struct MyErrorMgr
    {
        struct jpeg_error_mgr pub;	/* "public" fields */
        jmp_buf setjmp_buffer;	/* for return to caller */
    };
    
    typedef struct MyErrorMgr * MyErrorPtr;
    
    /*
     * Here's the routine that will replace the standard error_exit method:
     */
    
    METHODDEF(void)
    myErrorExit(j_common_ptr cinfo)
    {
        /* cinfo->err really points to a MyErrorMgr struct, so coerce pointer */
        MyErrorPtr myerr = (MyErrorPtr) cinfo->err;
        
        /* Always display the message. */
        /* We could postpone this until after returning, if we chose. */
        /* internal message function cann't show error message in some platforms, so we rewrite it here.
         * edit it if has version confilict.
         */
        //(*cinfo->err->output_message) (cinfo);
        char buffer[JMSG_LENGTH_MAX];
        (*cinfo->err->format_message) (cinfo, buffer);
        CCLOG("jpeg error: %s", buffer);
        
        /* Return control to the setjmp point */
        longjmp(myerr->setjmp_buffer, 1);
    }
}

namespace
{
    bool JPEGModuleSaveImage(const std::string &filePath, Image *image)
    {
        bool ret = false;
        do
        {
            struct jpeg_compress_struct cinfo;
            struct jpeg_error_mgr jerr;
            FILE * outfile;                 /* target file */
            JSAMPROW row_pointer[1];        /* pointer to JSAMPLE row[s] */
            int     row_stride;          /* physical row width in image buffer */
            
            cinfo.err = jpeg_std_error(&jerr);
            /* Now we can initialize the JPEG compression object. */
            jpeg_create_compress(&cinfo);
            
            CC_BREAK_IF((outfile = fopen(filePath.c_str(), "wb")) == nullptr);
            
            jpeg_stdio_dest(&cinfo, outfile);
            
            int width = image->getWidth();
            int height = image->getHeight();
            cinfo.image_width = width;    /* image width and height, in pixels */
            cinfo.image_height = height;
            cinfo.input_components = 3;       /* # of color components per pixel */
            cinfo.in_color_space = JCS_RGB;       /* colorspace of input image */
            
            jpeg_set_defaults(&cinfo);
            jpeg_set_quality(&cinfo, 90, true);
            
            jpeg_start_compress(&cinfo, true);
            
            row_stride = image->getWidth() * 3; /* JSAMPLEs per row in image_buffer */
            
            unsigned char *data = image->getData();
            if (image->hasAlpha())
            {
                unsigned char *tempData = static_cast<unsigned char*>(malloc(width * height * 3 * sizeof(unsigned char)));
                if (nullptr == tempData)
                {
                    jpeg_finish_compress(&cinfo);
                    jpeg_destroy_compress(&cinfo);
                    fclose(outfile);
                    break;
                }
                
                for (int i = 0; i < height; ++i)
                {
                    for (int j = 0; j < width; ++j)
                        
                    {
                        tempData[(i * width + j) * 3] = data[(i * width + j) * 4];
                        tempData[(i * width + j) * 3 + 1] = data[(i * width + j) * 4 + 1];
                        tempData[(i * width + j) * 3 + 2] = data[(i * width + j) * 4 + 2];
                    }
                }
                
                while (cinfo.next_scanline < cinfo.image_height)
                {
                    row_pointer[0] = & tempData[cinfo.next_scanline * row_stride];
                    jpeg_write_scanlines(&cinfo, row_pointer, 1);
                }
                
                if (tempData != nullptr)
                {
                    free(tempData);
                }
            }
            else
            {
                while (cinfo.next_scanline < cinfo.image_height)
                {
                    row_pointer[0] = & data[cinfo.next_scanline * row_stride];
                    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
                }
            }
            
            jpeg_finish_compress(&cinfo);
            fclose(outfile);
            jpeg_destroy_compress(&cinfo);
            
            ret = true;
        } while (0);
        return ret;
    }
    
    bool JPEGModuleInitWithJPEGData(const unsigned char *data, ssize_t dataLen, DataFromModule &dataFromJPEGInit)
    {
        /* these are standard libjpeg structures for reading(decompression) */
        struct jpeg_decompress_struct cinfo;
        /* We use our private extension JPEG error handler.
         * Note that this struct must live as long as the main JPEG parameter
         * struct, to avoid dangling-pointer problems.
         */
        struct MyErrorMgr jerr;
        /* libjpeg data structure for storing one row, that is, scanline of an image */
        JSAMPROW row_pointer[1] = {0};
        unsigned long location = 0;
        unsigned int i = 0;
        
        bool ret = false;
        do
        {
            /* We set up the normal JPEG error routines, then override error_exit. */
            cinfo.err = jpeg_std_error(&jerr.pub);
            jerr.pub.error_exit = myErrorExit;
            /* Establish the setjmp return context for MyErrorExit to use. */
            if (setjmp(jerr.setjmp_buffer)) {
                /* If we get here, the JPEG code has signaled an error.
                 * We need to clean up the JPEG object, close the input file, and return.
                 */
                jpeg_destroy_decompress(&cinfo);
                break;
            }
            
            /* setup decompression process and source, then read JPEG header */
            jpeg_create_decompress( &cinfo );
            
#ifndef CC_TARGET_QT5
            jpeg_mem_src(&cinfo, const_cast<unsigned char*>(data), dataLen);
#endif /* CC_TARGET_QT5 */
            
            /* reading the image header which contains image information */
#if (JPEG_LIB_VERSION >= 90)
            // libjpeg 0.9 adds stricter types.
            jpeg_read_header(&cinfo, true);
#else
            jpeg_read_header(&cinfo, true);
#endif
            
            // we only support RGB or grayscale
            if (cinfo.jpeg_color_space == JCS_GRAYSCALE)
            {
                dataFromJPEGInit.renderFormat = Texture2D::PixelFormat::I8;
            }else
            {
                cinfo.out_color_space = JCS_RGB;
                dataFromJPEGInit.renderFormat = Texture2D::PixelFormat::RGB888;
            }
            
            /* Start decompression jpeg here */
            jpeg_start_decompress(&cinfo);
            
            /* init image info */
            dataFromJPEGInit.width = cinfo.output_width;
            dataFromJPEGInit.height = cinfo.output_height;
            row_pointer[0] = static_cast<unsigned char*>(malloc(cinfo.output_width*cinfo.output_components * sizeof(unsigned char)));
            CC_BREAK_IF(! row_pointer[0]);
            
            dataFromJPEGInit.dataLength = cinfo.output_width*cinfo.output_height*cinfo.output_components;
            dataFromJPEGInit.data = static_cast<unsigned char*>(malloc(dataFromJPEGInit.dataLength * sizeof(unsigned char)));
            
            unsigned char* imageData = dataFromJPEGInit.data;
            CC_BREAK_IF(! imageData);
            
            
            /* now actually read the jpeg into the raw buffer */
            /* read one scan line at a time */
            while( cinfo.output_scanline < cinfo.output_height )
            {
                jpeg_read_scanlines( &cinfo, row_pointer, 1 );
                for( i=0; i<cinfo.output_width*cinfo.output_components;i++)
                {
                    imageData[location++] = row_pointer[0][i];
                }
            }
            
            /* When read image file with broken data, jpeg_finish_decompress() may cause error.
             * Besides, jpeg_destroy_decompress() shall deallocate and release all memory associated
             * with the decompression object.
             * So it doesn't need to call jpeg_finish_decompress().
             */
            //jpeg_finish_decompress( &cinfo );
            jpeg_destroy_decompress( &cinfo );
            /* wrap up decompression, destroy objects, free pointers and close open files */        
            ret = true;
        } while (0);
        
        if (row_pointer[0] != nullptr)
        {
            free(row_pointer[0]);
        }
        
        return ret;
    }



    class RegisterJPEG
    {
    public:
        RegisterJPEG()
        {
            static struct JPEGModule jpegModule;
            jpegModule.saveImage = JPEGModuleSaveImage;
            jpegModule.initWithJPEGData = JPEGModuleInitWithJPEGData;
            ModuleManager::registerModule("jpeg", &jpegModule);
        }
    };

    static RegisterJPEG registerJPEG;

}


