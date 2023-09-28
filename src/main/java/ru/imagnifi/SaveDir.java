package ru.imagnifi;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class SaveDir {
    public static void main(String[] args) {
        String installPath = args[0];
        File file = new File(installPath + "/SmartCalc.command");
        try {
            BufferedReader bufIn = new BufferedReader(new FileReader(file));
            List<String> listBuffer = new ArrayList<>();
            String str;
            while ((str = bufIn.readLine()) != null){
                if(str.contains("installPath=")){
                    str = str.substring(0,12) + installPath;
                }
                listBuffer.add(str);
            }
            bufIn.close();
            BufferedWriter bufOut = new BufferedWriter(new FileWriter(file));
            for (String s : listBuffer) {
                bufOut.write(s + "\n");
            }
            bufOut.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
