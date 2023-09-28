package ru.imagnifi;

import javafx.application.Application;

import java.io.UnsupportedEncodingException;
import java.lang.reflect.Field;
import java.net.URLDecoder;

public class Main {
    public static String jpath;

    static {
        try {
            jpath = URLDecoder.decode((Main.class.getProtectionDomain()
                                                 .getCodeSource()
                                                 .getLocation()
                                                 .getPath()
                                                 .replace("Smart_Calc_3_0.jar", "")), "UTF-8");
        } catch (UnsupportedEncodingException e) {
            throw new RuntimeException(e);
        }
        if (System.getProperty("os.name")
                  .toLowerCase()
                  .contains("windows") && jpath.startsWith("/")) {
            jpath = jpath.substring(1);
        }
        System.setProperty("java.library.path", jpath + "classes/ru/imagnifi");
        try {
            Field fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
            fieldSysPath.setAccessible(true);
            fieldSysPath.set(null, null);
        } catch (IllegalAccessException | NoSuchFieldException e) {
            throw new RuntimeException(e);
        }
        System.setProperty("PATH_TO_SMARTCALC_3_0", jpath);
    }

    public static void main(String[] args) throws NoSuchFieldException, IllegalAccessException {

//        String path = System.getProperty("java.library.path");
//        System.out.println("java.lybrary.path = " + path);
//
//        System.out.println("jpath = " + jpath);
//
//        String clpath = System.getProperty("user.dir");
//        System.out.println("user.dir = " + clpath);
//
//        System.out.println("PATH_TO_SMARTCALC_3_0 = " + System.getProperty("PATH_TO_SMARTCALC_3_0"));
//
//        String path2 = System.getProperty("java.home");
//        System.out.println("java.home = " + path2);
//
//        String path3 = System.getProperty("java.class.path");
//        System.out.println("java.class.path = " + path3);

        //        System.getProperties().list(System.out);
//        String path4 = System.getProperty("class.path");
//        System.out.println("class.path = " + path4);
//        `boolean isWindows = System.getProperty("os.name")
//                                  .toLowerCase()
//                                  .contains("windows");
//        System.out.println("isWindows = " + isWindows);
//        String user = System.getProperty("user.name");
//        System.out.println("user = " + user);`

        Application.launch(App.class, args);
    }
}
