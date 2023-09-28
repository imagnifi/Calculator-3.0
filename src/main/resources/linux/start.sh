#!/bin/bash
chmod 555 $1/Uninstaller/uninstaller.jar
cd $1 && java -Djava.library.path="classes/ru/imagnifi" -jar Smart_Calc_3_0.jar
