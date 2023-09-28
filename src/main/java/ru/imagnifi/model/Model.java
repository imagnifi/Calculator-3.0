package ru.imagnifi.model;

import org.bytedeco.javacpp.*;
import org.bytedeco.javacpp.annotation.*;

import java.util.Vector;


@Platform(include = "model/Model.cpp")
@Namespace("s21")
public class Model extends Pointer {

    static {
        Loader.load();
    }

    public Model() {
        allocate();
        init_text_data();
        draw_sc_init();
    }

    private native void allocate();

    public native @StdString String button_execute(String operator, String input);

    public native @StdVector double[] make_function_graph(String inp);

    public native @StdVector double[] getF_X();

    public native void init_text_data();
    public native void draw_sc_init();
}
