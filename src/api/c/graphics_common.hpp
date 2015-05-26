/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#pragma once

#if defined(WITH_GRAPHICS)

#include <af/graphics.h>
#include <forge.h>

#include <map>

// default to f32(float) type
template<typename T>
GLenum getGLType();

// Print for OpenGL errors
// Returns 1 if an OpenGL error occurred, 0 otherwise.
GLenum glErrorSkip(const char *msg, const char* file, int line);
GLenum glErrorCheck(const char *msg, const char* file, int line);
GLenum glForceErrorCheck(const char *msg, const char* file, int line);

#define CheckGL(msg)      glErrorCheck     (msg, __FILE__, __LINE__)
#define ForceCheckGL(msg) glForceErrorCheck(msg, __FILE__, __LINE__)
#define CheckGLSkip(msg)  glErrorSkip      (msg, __FILE__, __LINE__)

namespace graphics
{

enum Defaults {
    WIDTH = 1280,
    HEIGHT= 720
};

typedef std::map<size_t, fg::Image*> ImageMap_t;
typedef std::map<size_t, fg::Plot*> PlotMap_t;
typedef std::map<size_t, fg::Histogram*> HistogramMap_t;

typedef ImageMap_t::iterator ImgMapIter;
typedef PlotMap_t::iterator PltMapIter;
typedef HistogramMap_t::iterator HstMapIter;

/**
 * ForgeManager class follows a single pattern. Any user of this class, has
 * to call ForgeManager::getInstance inorder to use Forge resources for rendering.
 * It manages the windows, and other renderables (given below) that are drawed
 * onto chosen window.
 * Renderables:
 *             fg::Image
 *             fg::Plot
 *             fg::Histogram
 * */
class ForgeManager
{
    private:
        ImageMap_t      mImgMap;
        PlotMap_t       mPltMap;
        HistogramMap_t  mHstMap;

    public:
        static ForgeManager& getInstance();
        ~ForgeManager();

        fg::Font* getFont(const bool dontCreate=false);
        fg::Window* getMainWindow(const bool dontCreate=false);
        fg::Image* getImage(int w, int h, fg::ColorMode mode, GLenum type);
        fg::Plot* getPlot(int nPoints, GLenum type);
        fg::Histogram* getHistogram(int nBins, GLenum type);

    protected:
        ForgeManager() {}
        ForgeManager(ForgeManager const&);
        void operator=(ForgeManager const&);
        void destroyResources();
};

}

#define MAIN_WINDOW graphics::ForgeManager::getInstance().getMainWindow(true)

#endif
