package ru.imagnifi.view;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import lombok.SneakyThrows;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.core.LoggerContext;
import org.apache.logging.log4j.core.appender.RollingFileAppender;
import org.apache.logging.log4j.core.appender.rolling.PatternProcessor;
import org.apache.logging.log4j.core.config.Configuration;
import ru.imagnifi.Main;
import ru.imagnifi.viewModel.ViewModel;

import javax.swing.*;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Field;
import java.net.URL;
import java.nio.file.Files;
import java.util.Objects;
import java.util.Properties;

//import static sun.rmi.runtime.Log.getSource;

public class View extends Application {

    @FXML
    public Label resultExpression;
    @FXML
    public Button sin;
    @FXML
    public Button cos;
    @FXML
    public Button tan;
    @FXML
    public Button num7;
    @FXML
    public Button num8;
    @FXML
    public Button num9;
    @FXML
    public Button slash;
    @FXML
    public Button stepen;
    @FXML
    public Button AC;
    @FXML
    public Button asin;
    @FXML
    public Button acos;
    @FXML
    public Button atan;
    @FXML
    public Button num4;
    @FXML
    public Button num5;
    @FXML
    public Button num6;
    @FXML
    public Button umnojit;
    @FXML
    public Button D_f;
    @FXML
    public Button R;
    @FXML
    public Button log;
    @FXML
    public Button ln;
    @FXML
    public Button sqrt;
    @FXML
    public Button num1;
    @FXML
    public Button num2;
    @FXML
    public Button num3;
    @FXML
    public Button minus;
    @FXML
    public Button E_f;
    @FXML
    public Button f_x;
    @FXML
    public Button mod;
    @FXML
    public Button leftBracket;
    @FXML
    public Button num0;
    @FXML
    public Button point;
    @FXML
    public Button x;
    @FXML
    public Button plus;
    @FXML
    public Button ravno;
    @FXML
    public Button E;
    @FXML
    public Button rightBracket;
    private final ViewModel viewModel;
    public GridPane gridPane;
    @FXML
    public Button Help;
    @FXML
    public Button Logger;
    @FXML
    private boolean dot;
    private final ViewLog logger = new ViewLog();
    private RollingFileAppender appender1;

    @FXML
    public void initialize() {
        Properties properties = new Properties();
        try {
            String path = Main.jpath + "classes/ru/imagnifi/config.properties";
            File file = new File(path);
            InputStream is = Files.newInputStream(file.toPath());
            properties.load(is);
            ObservableList<Node> list = gridPane.getChildren();
            String buttonStyle =
                    properties.getProperty("buttonColor") + " " + properties.getProperty("textSize") + " " +
                            properties.getProperty("textWrap");
            for (Node node : list) {
                if (node instanceof Button) {
                    node.setStyle(buttonStyle);
                }
            }
            Help.setStyle(buttonStyle);
            Logger.setStyle(buttonStyle);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        LoggerContext ctx = (LoggerContext) LogManager.getContext(false);
        Configuration config = ctx.getConfiguration();
        appender1 = config.getAppender("rollingFile");
    }

    public View() {
        viewModel = new ViewModel();
        logger.fillTable();
    }

    public double minX = -10000;
    public double maxX = 10000;
    public double minY = -1000;
    public double maxY = 1000;


    @FXML
    public void compute(ActionEvent action) {
        String operator = ((Button) action.getSource()).getText();
        String expression = resultExpression.getText();
        String result = viewModel.compute(operator, resultExpression.getText());
        resultExpression.setText(result);
        ViewLog.logMessage(expression + " = " + result);
    }

    public void addExpression(ActionEvent action) {
        Button obj = (Button) action.getSource();
        if (resultExpression.getText()
                            .equals("0") && !obj.getText()
                                                .equals(".")) {
            resultExpression.setText(obj.getText());
        } else {
            if (obj.getText()
                   .equals(".")) {
                if (!dot) {
                    resultExpression.setText(resultExpression.getText() + obj.getText());
                    dot = true;
                }
            } else {
                resultExpression.setText(resultExpression.getText() + obj.getText());
            }
        }
        if (obj.getText()
               .equals("+") || obj.getText()
                                  .equals("-") || obj.getText()
                                                     .equals("*") || obj.getText()
                                                                        .equals("/") || obj.getText()
                                                                                           .equals("^")) {
            dot = false;
        }
    }

    public void deleteAll() {

        resultExpression.setText("0");

    }

    public void deleteOneLast() {
        if (resultExpression.getText()
                            .length() > 1) {
            resultExpression.setText(resultExpression.getText()
                                                     .substring(0, resultExpression.getText()
                                                                                   .length() - 1));

        } else {
            resultExpression.setText("0");
        }
    }

    public void paintGraph() {
        double[] f_y;
        double[] f_x;
        f_y = viewModel.computeY(resultExpression.getText());
        f_x = viewModel.computeX();
        XYChart.Series<Number, Number> series = new XYChart.Series<>();
        series.setName(resultExpression.getText());
        for (int x = 0; x < 2000; x++) {
            series.getData()
                  .add(new XYChart.Data<>(f_x[x], f_y[x]));
        }
        NumberAxis yAxis = new NumberAxis("Y", minY, maxY, (Math.abs(minY) + Math.abs(maxY)) / 2000);

        NumberAxis xAxis = new NumberAxis("X", minX, maxX, (Math.abs(minX) + Math.abs(maxX)) / 2000);
        LineChart<Number, Number> lineChart = new LineChart<>(xAxis, yAxis);
        lineChart.setTitle("Graph of function - " + resultExpression.getText());
        lineChart.getData()
                 .add(series);
        lineChart.setCreateSymbols(false);
        StackPane pane = new StackPane();
        pane.getChildren()
            .add(lineChart);
        Scene scene = new Scene(pane, 600, 600);
        Stage stage = new Stage();
        stage.initModality(Modality.NONE);
        stage.setTitle("Graphs");
        stage.setScene(scene);
        stage.show();
    }

    public void loggerView() {
        logger.refreshTable();
        StackPane pane = new StackPane();
        Button clearHistory = new Button("Clear History");
        Button writeExpression = new Button("Write Expression");
        ComboBox<String> rotations = new ComboBox<>(
                FXCollections.observableArrayList("rotation: minute", "rotation: hour", "rotation: day",
                        "rotation: month"));
        rotations.setEditable(false);
        rotations.setValue(rotation());
        TableView<ViewLog.ResultData> table = logger.table;
        pane.getChildren()
            .addAll(table, writeExpression, clearHistory, rotations);
        StackPane.setMargin(table, new Insets(40, 0, 0, 0));
        StackPane.setMargin(clearHistory, new Insets(5, 5, 5, 5));
        StackPane.setMargin(writeExpression, new Insets(5, 5, 5, 5));
        StackPane.setMargin(rotations, new Insets(5, 5, 5, 5));
        StackPane.setAlignment(writeExpression, Pos.TOP_LEFT);
        StackPane.setAlignment(clearHistory, Pos.TOP_RIGHT);
        StackPane.setAlignment(rotations, Pos.TOP_CENTER);

        rotations.setOnAction(event -> changeRotations(rotations));

        clearHistory.setOnAction(event -> clearHistory());

        Stage stage = new Stage();
        writeExpression.setOnAction(event -> writeExpr(stage));

        table.setOnMousePressed(event -> {
            if (event.isPrimaryButtonDown() && event.getClickCount() == 2) {
                writeExpr(stage);
            }
        });
        Scene scene = new Scene(pane, 600, 600);
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.setTitle("Logs");
        stage.setScene(scene);
        stage.show();
    }

    private String rotation() {
        String result = null;
        String pattern = appender1.getFilePattern();
        if (pattern.replace("}.log", "")
                   .endsWith("HH")) {
            result = "rotation: hour";
        } else if (pattern.replace("}.log", "")
                          .endsWith("dd")) {
            result = "rotation: day";
        } else if (pattern.replace("}.log", "")
                          .endsWith("MM")) {
            result = "rotation: month";
        } else if (pattern.replace("}.log", "")
                          .endsWith("mm")) {
            result = "rotation: minute";
        }
        return result;
    }

    private void clearHistory() {
        try {
            ViewLog.clearLogFile();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        logger.refreshTable();
    }

    private void changeRotations(ComboBox<String> comboBox) {
        String pattern = "hour";
        String value = comboBox.getValue()
                               .replace("rotation: ", "");
        switch (value) {
            case "hour":
                pattern = "${LOG_DIR}/logs_%d{yyyy-MM-dd-HH}.log";
                break;
            case "day":
                pattern = "${LOG_DIR}/logs_%d{yyyy-MM-dd}.log";
                break;
            case "month":
                pattern = "${LOG_DIR}/logs_%d{yyyy-MM}.log";
                break;
            case "minute":
                pattern = "${LOG_DIR}/logs_%d{yyyy-MM-dd-HH-mm}.log";
                break;
        }
        try {
            Field filePattern = appender1.getClass()
                                         .getDeclaredField("filePattern");
            filePattern.setAccessible(true);
            filePattern.set(appender1, pattern);
            filePattern.setAccessible(false);
            appender1.getManager()
                     .setPatternProcessor(new PatternProcessor(pattern));
        } catch (NoSuchFieldException | IllegalAccessException e) {
            throw new RuntimeException(e);
        }
    }

    private void writeExpr(Stage stageParent) {
        ViewLog.ResultData result = logger.getSelectedExpression();
//            resultExpression.setText("0");
        if (result != null) {
            resultExpression.setText(result.getExpression());
            stageParent.close();
        } else {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText(null);
            alert.setContentText("Please, select row.");
            alert.initStyle(StageStyle.DECORATED);
            Stage stage = (Stage) alert.getDialogPane()
                                       .getScene()
                                       .getWindow();
            stage.getIcons()
                 .add(new Image(Objects.requireNonNull(getClass().getResource("/images/calculator1.ico"))
                                       .toString()));
            alert.showAndWait();
        }
    }

    @SneakyThrows
    public void helpView() {
        URL url = this.getClass()
                      .getResource("/ru/imagnifi/help.html");
        JFrame frame = new JFrame();
        JEditorPane edPane = new JEditorPane(url);
        edPane.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(edPane);
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setTitle(" Help for SmartCalc ");
        frame.setSize(700, 500);
        frame.setLocationRelativeTo(null);
        frame.setResizable(false);
        frame.getContentPane()
             .add(scrollPane);
        frame.setVisible(true);
    }

    public void setF(ActionEvent action) {
        Button but = (Button) action.getSource();
        double value = Double.parseDouble(resultExpression.getText());
        if (but.getText()
               .equals("E(f)")) {
            minY = -value;
            maxY = value;
            resultExpression.setText("0");
        } else if (but.getText()
                      .equals("D(f)")) {
            minX = -value;
            maxX = value;
            resultExpression.setText("0");
        }

    }

    @Override
    public void start(Stage primaryStage) {

    }


}
