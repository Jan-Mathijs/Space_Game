#include "LinuxInput.h"
#ifdef RASPBERRY

LinuxInput::LinuxInput()
{
    
}

LinuxInput::~LinuxInput()
{

}

void LinuxInput::CheckInput()
{
    //if (theInput != nullptr) {
        //key input
        if (theInput->Keys[KEY_W] == TRUE)
        {
            inputKeyW = true;
        }
        else {
            inputKeyW = false;
        }
        if (theInput->Keys[KEY_A] == TRUE)
        {
            // inputKeyW = true;
        }
        else {

        }
        if (theInput->Keys[KEY_S] == TRUE)
        {
            inputKeyS = true;
        }
        else {
            inputKeyS = false;
        }
        if (theInput->Keys[KEY_D] == TRUE)
        {

        }

        if (theInput->Keys[KEY_UP] == TRUE)
        {
            inputKeyArrowUp = true;
        }
        else {
            inputKeyArrowUp = false;
        }
        if (theInput->Keys[KEY_DOWN] == TRUE)
        {
            inputKeyArrowDown = true;
        }
        else {
            inputKeyArrowDown = false;
        }

        if (theInput->Keys[KEY_LEFT] == TRUE)
        {
            inputKeyArrowLeft = true;
        }
        else {
            inputKeyArrowLeft = false;
        }
        if (theInput->Keys[KEY_RIGHT] == TRUE)
        {
            inputKeyArrowRight = true;
        }
        else {
            inputKeyArrowRight = false;
        }

        if (theInput->Keys[KEY_E] == TRUE)
        {
            inputKeyE = true;
        }
        else {
            inputKeyE = false;
        }
        if (theInput->Keys[KEY_Q] == TRUE)
        {
            inputKeyQ = true;
        }
        else {
            inputKeyQ = false;
        }

        if (theInput->Keys[KEY_L] == TRUE)
        {
            inputKeyL = true;
        }
        else {
            inputKeyL = false;
        }

        if (theInput->Keys[KEY_Z] == TRUE)
        {
            inputKeyZ = true;
        }
        else {
            inputKeyZ = false;
        }


        if (theInput->TheMouse.RelX > 0)
        {
            //  LocalRotations.x += .30;
           //   theInput->TheMouse.RelX = 0;

        }
        else if (theInput->TheMouse.RelX < 0)
        {
            // DegreeRotations.z 
          //  LocalRotations.z -= .30f;//= DEG2RAD(DegreeRotations.z);
           // theInput->TheMouse.RelX = 0;
        }
        else
        {
            // DegreeRotations.z = DegreeRotations.z;
             //LocalRotations.z = DEG2RAD(DegreeRotations.z);
        }

        if (theInput->TheMouse.RelY > 0)
        {

            // LocalRotations.x += .30f;//= DEG2RAD(DegreeRotations.x);
           //  theInput->TheMouse.RelY = 0;
        }
        else if (theInput->TheMouse.RelY < 0)
        {
            //   DegreeRotations.x -= 1.0f;
           // Rotations.x -= 1.0f;// DEG2RAD(DegreeRotations.x);
           // theInput->TheMouse.RelY = 0;
        }
    //}
   
}

#endif
