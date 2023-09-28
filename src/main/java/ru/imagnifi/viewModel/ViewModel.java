package ru.imagnifi.viewModel;

import ru.imagnifi.model.Model;

public class ViewModel {

    private final Model cppModel;


    public ViewModel() {
        cppModel = new Model();
    }

    public String compute(String operator, String expression) {
        String result = "0";
        if (operator.equals("=")) {
            result = cppModel.button_execute(operator, expression);
        }
        return result;
    }

    public double[] computeY(String inp){
        double[] f_y1 = cppModel.make_function_graph(inp);
        return f_y1;
    }

    public double[] computeX() {
        return cppModel.getF_X();
    }

}
