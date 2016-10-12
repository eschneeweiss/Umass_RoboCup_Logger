//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
/*!
file    main.cpp
brief   main function
author  Eddy Schneeweiss (C) 2016
*/
//========================================================================

#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <stdio.h>

char path[80];
char filename[80];
unsigned int frame = 0;
double speed = 1;

void parseArgs(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    parseArgs(argc, argv);
    QApplication app(argc, argv);
    MainWindow *mw;
    mw = new MainWindow(path, filename, frame, speed);
    mw->show();

    int retVal = app.exec();
    //clean up:
    delete mw;

    return retVal;
}

//arguments: argc, argv
//Iterates through the arguments and sets the aplication initualization variables
// -p ssl_file_path, -f playback_filename, -n staring_frame_number, -s staring_frame_speed
void parseArgs(int argc, char *argv[]){
    for (int i = 1; i < argc; i++){
        char *opt = argv[i];

        if (*opt != '-'){
            //complain
            continue;
        }
        opt++;//point to second byte
        i++;
        if (i >= argc){
            //complain
            break;
        }

        switch(*opt){
            case 'p':
                strcpy(path, argv[i]);break;
            case 'f':
                strcpy(filename, argv[i]);break;
            case 'n':
                frame = atoi(argv[i]);break;
            case 's':
                speed = atof(argv[i]);break;
        }
    }
}
