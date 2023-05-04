#pragma once
#include "Translator.h"

    void Translator::getFrame()
    {
        cap >> frame;
        if (frame.empty())
        {
            throw;
        }
        this->frame = frame;
    }
    void Translator::showFrames()
    {
        imshow("Frame", frame);
        waitKey(1);
    }

    Translator::~Translator() {
        cap.release();
        destroyAllWindows();
    }
