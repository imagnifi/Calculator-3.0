package ru.imagnifi;



import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;
import org.junit.jupiter.params.provider.CsvSource;
import ru.imagnifi.model.Model;

import java.lang.reflect.Field;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

//@Disabled
public class SmartCalcModelTest {
    static {
        System.setProperty("java.library.path", "target/classes/ru/imagnifi");
        try {
            Field fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
            fieldSysPath.setAccessible(true);
            fieldSysPath.set(null, null);
            fieldSysPath.setAccessible(false);
        } catch (IllegalAccessException | NoSuchFieldException e) {
            throw new RuntimeException(e);
        }
    }
    Model model1 = new Model();
    @ParameterizedTest(name = "{index}) {0} = {1}")
    @CsvFileSource(resources = "/calc_equals.csv")
    public void testButtonExecute(String expression, String res) {
        String result = model1.button_execute("=", expression);
        assertEquals(res, result);
    }
    @ParameterizedTest()
    @CsvSource({"50", "100", "1000"})
    public void testMakeFunctionGraph(String input) {
        double[] massY = model1.make_function_graph(input);
        assertEquals(2000, massY.length);
        for (double val : massY) {
            assertEquals(val, Double.parseDouble(input));
        }
    }
    @Test
    public void testGetF_X() {
        model1.make_function_graph("1+1");
        double[] massX = model1.getF_X();
        assertEquals(2000, massX.length);
        for (double x : massX) {
            assertNotEquals(0.0, x);
        }
    }
}
