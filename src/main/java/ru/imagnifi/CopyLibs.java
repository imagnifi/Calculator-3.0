package ru.imagnifi;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;


public class CopyLibs {
    private enum OS {WIN, LIN, MAC}
    //     private static String url = "https://github.com/imagnifi/SmartCalcLib/blob/main/";
//     private static String postfix  = "&raw=true";
    private static final String url = "https://raw.githubusercontent.com/imagnifi/SmartCalcLib/main/";
    private static final String postfix = "";
    private static final String[] files =
            {"aether-api-1.0.0.v20140518.jar", "aether-impl-1.0.0.v20140518.jar",
                    "aether-spi-1.0.0.v20140518.jar", "aether-util-1.0.0.v20140518.jar",
                    "ant-1.9.9.jar", "ant-launcher-1.9.9.jar", "aopalliance-1.0.jar",
                    "apache-mime4j-core-0.7.2.jar", "apache-mime4j-dom-0.7.2.jar",
                    "apiguardian-api-1.1.2.jar", "asm-debug-all-4.1.jar", "aspectjrt-1.8.0.jar",
                    "batik-awt-util-1.6.jar", "batik-dom-1.6.jar", "batik-svg-dom-1.6.jar", "batik-svggen-1.6.jar",
                    "batik-util-1.6.jar", "batik-xml-1.6.jar", "bcmail-jdk15on-1.52.jar",
                    "bcpkix-jdk15on-1.54.jar", "bcprov-ext-jdk15on-1.54.jar", "bcprov-jdk15on-1.54.jar",
                    "boilerpipe-1.1.0.jar", "bzip2-0.9.1.jar", "c3p0-0.9.1.1.jar", "cdi-api-1.0.jar",
                    "cdm-4.5.5.jar", "commons-cli-1.3.1.jar", "commons-codec-1.9.jar", "commons-compress-1.12.jar",
                    "commons-csv-1.0.jar", "commons-exec-1.3.jar", "commons-io-2.5.jar", "commons-lang3-3.5.jar",
                    "commons-logging-1.1.1.jar", "commons-logging-api-1.1.jar", "commons-vfs2-2.0.jar",
                    "ehcache-core-2.6.2.jar", "fontbox-1.8.10.jar", "geoapi-3.0.0.jar", "grib-4.5.5.jar",
                    "guava-16.0.1.jar", "hamcrest-core-1.1.jar", "httpclient-4.2.6.jar", "httpcore-4.2.5.jar",
                    "httpmime-4.2.6.jar", "httpservices-4.5.5.jar", "icepdf-core-6.2.2.jar",
                    "icepdf-viewer-6.2.2.jar", "isoparser-1.0.2.jar", "jai_imageio-1.1.pom",
                    "java-libpst-0.8.1.jar", "javacpp-1.5.8.jar", "javafx-1.8.0.jar", "javafx-base-1.8.0.jar",
                    "javafx-controls-1.8.0.jar", "javafx-fxml-1.8.0.jar", "javafx-graphics-1.8.0.jar",
                    "javafx-media-1.8.0.jar", "javax.inject-1.jar", "jcip-annotations-1.0.jar",
                    "jcommander-1.35.jar", "jdom-1.0.jar", "jdom2-2.0.5.jar", "jempbox-1.8.10.jar",
                    "jhighlight-1.0.2.jar", "jj2000-5.2.jar", "jline-2.12.1.jar", "jmatio-1.0.jar",
                    "jna-4.1.0.jar", "joda-time-2.2.jar", "json-simple-1.1.1.jar", "jsoup-1.7.2.jar",
                    "jsr-275-0.9.3.jar", "jsr250-api-1.0.jar", "junit-4.10.jar",
                    "junit-platform-commons-1.9.2.jar", "junit-platform-engine-1.9.2.jar",
                    "juniversalchardet-1.0.3.jar", "junrar-0.7.jar", "jwnl-1.3.3.jar", "kunstoff-laf-2.0.2.jar",
                    "laf-plugin-7.3.jar", "laf-widget-7.3.jar", "log4j-api-2.20.0.jar", "log4j-core-2.20.0.jar",
                    "looks-2.2.2.jar", "maven-aether-provider-3.2.5.jar", "maven-artifact-3.2.5.jar",
                    "maven-compat-3.2.5.jar", "maven-core-3.2.5.jar", "maven-model-3.2.5.jar",
                    "maven-model-builder-3.2.5.jar", "maven-plugin-api-3.2.5.jar",
                    "maven-repository-metadata-3.2.5.jar", "maven-scm-api-1.4.jar",
                    "maven-scm-provider-svn-commons-1.4.jar", "maven-scm-provider-svnexe-1.4.jar",
                    "maven-settings-3.2.5.jar", "maven-settings-builder-3.2.5.jar", "metadata-extractor-2.8.0.jar",
                    "netcdf4-4.5.5.jar", "opennlp-maxent-3.0.3.jar", "opennlp-tools-1.5.3.jar",
                    "opentest4j-1.2.0.jar", "org.eclipse.sisu.inject-0.3.0.M1.jar",
                    "org.eclipse.sisu.plexus-0.3.0.M1.jar", "pdfbox-1.8.10.jar", "picocontainer-2.15.jar",
                    "plexus-cipher-1.4.jar", "plexus-classworlds-2.5.2.jar",
                    "plexus-component-annotations-1.5.5.jar", "plexus-interpolation-1.21.jar",
                    "plexus-sec-dispatcher-1.3.jar", "plexus-utils-3.0.20.jar", "poi-3.12.jar",
                    "poi-ooxml-3.12.jar", "poi-ooxml-schemas-3.12.jar", "poi-scratchpad-3.12.jar",
                    "protobuf-java-2.5.0.jar", "quartz-2.2.0.jar", "regexp-1.3.jar", "rome-1.0.jar",
                    "sis-metadata-0.5.jar", "sis-netcdf-0.5.jar", "sis-referencing-0.5.jar", "sis-storage-0.5.jar",
                    "sis-utility-0.5.jar", "sisu-guice-3.2.3-no_aop.jar", "slf4j-api-1.7.7.jar",
                    "substance-7.3.jar", "tagsoup-1.2.1.jar", "tika-core-1.9.jar", "tika-parsers-1.9.jar",
                    "trident-7.3-swing.jar", "udunits-4.5.5.jar", "vorbis-java-core-0.6.jar",
                    "vorbis-java-tika-0.6.jar", "wagon-provider-api-2.8.jar", "xmlbeans-2.6.0.jar",
                    "xmpcore-5.1.2.jar", "xz-1.6.jar"};


//    public void run(AbstractUIProcessHandler handler, String[] args) {

//        String patToLib = args[0] + "/lib/";
//        File dir = new File(patToLib);
//        if(!dir.exists()){
//            dir.mkdir();
//        }
//        for (String s : files) {
//            loadFile(url, s, postfix, patToLib);
//        }
//    }

    private static void loadFile(String fileName, String dir) {
        String pathUrl = CopyLibs.url + fileName + CopyLibs.postfix;
        try {
            InputStream in = new URL(pathUrl).openStream();
            Files.copy(in, Paths.get(dir + fileName), StandardCopyOption.REPLACE_EXISTING);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        String patToLib = args[0] + "/lib/";
        File dir = new File(patToLib);
        if(!dir.exists()){
            dir.mkdir();
        }
        for (String s : files) {
            loadFile(s, patToLib);
        }
        OS sys = getOS();
        if (sys != null) {
            loadJniLib(sys, args[0]);
        } else {
            throw new RuntimeException("System is not supported.");
        }
    }

    private static void loadJniLib(OS sys, String installPath){
        String path = installPath + "/classes/ru/imagnifi/";
        if (sys == OS.WIN){
            loadFile("jnijavacpp.obj", path);
            loadFile("jniModel.dll", path);
            loadFile("jniModel.exp", path);
            loadFile("jniModel.lib", path);
            loadFile("jniModel.obj", path);
        } else if (sys == OS.LIN) {
            loadFile("libjniModel.so", path);
        } else if (sys == OS.MAC) {
            loadFile("libjniModel.dylib", path);
        }
    }

    private static OS getOS(){
        OS system = null;
        String res = System.getProperty("os.name").toLowerCase().trim();
        if (res.contains("windows")){
            system = OS.WIN;
        } else if (res.contains("linux")){
            system = OS.LIN;
        } else if (res.contains("mac")) {
            system = OS.MAC;
        }
        return system;
    }



//    public static void main(String[] args) {
//        File dir = new File("lib");
//        try {
//            Git.cloneRepository()
//               .setURI("https://github.com/imagnifi/SmartCalcLib.git")
//               .setDirectory(dir)
//               .call();
//        } catch (GitAPIException e) {
//            throw new RuntimeException(e);
//        }
//    }


}
