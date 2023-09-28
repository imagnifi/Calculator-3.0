package ru.imagnifi.view;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.SneakyThrows;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.imagnifi.Main;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import static java.nio.file.StandardOpenOption.TRUNCATE_EXISTING;

//@Slf4j

public class ViewLog {
    public static final String PATH_LOGS = Main.jpath + "logs";
    public static final String PATH_LOGS_FILE = Main.jpath + "logs/logs.log";
    private final ObservableList<ResultData> listOfResultData = FXCollections.observableArrayList();

    public TableView<ResultData> table = new TableView<ResultData>();

    //    static Logger log = LogManager.getLogger(LogManager.ROOT_LOGGER_NAME);
//    static Logger log = LogManager.getRootLogger();
//    static Logger log = LogManager.getLogger(ViewLog.class.getName());
//    static Logger log = LogManager.getLogger();
    static Logger log = LogManager.getLogger(ViewLog.class);

    @SneakyThrows
    public ViewLog() {
        File logDir = new File(PATH_LOGS);
//        logDir.setReadable(true);
//        logDir.setWritable(true);
        if (!logDir.exists()) {
            if (!logDir.mkdir()) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("SmartCalc: cant create directory.");
                alert.setContentText(
                        "Directory \"" + logDir.getAbsolutePath() + "\" cannot create, not enough permissions !");
                alert.showAndWait();
            }
        }
    }

    static public void logMessage(String mess) {
        log.info(mess);
    }

    public void fillListOfResultData() throws IOException {
        File file = new File(PATH_LOGS_FILE);
        if (file.exists()) {
            FileReader fileRead = new FileReader(file);
            BufferedReader reader = new BufferedReader(fileRead);
            String oneLine = reader.readLine();
            listOfResultData.clear();
            while (oneLine != null) {
                String[] split = oneLine.split(" expression: ");
                String[] split1 = split[0].split(" ");
                listOfResultData.add(
                        new ResultData(split1[0], split1[1], split1[2], split[0].substring(26), split[1].split("=")[0],
                                split[1].split("=")[1]));
                oneLine = reader.readLine();
            }
        }
    }

    public ResultData getSelectedExpression() {
        return table.getSelectionModel()
                    .getSelectedItem();
    }

    @SneakyThrows
    static public void clearLogFile() throws IOException {
        Path path = Paths.get(PATH_LOGS_FILE);
        File file = new File(PATH_LOGS_FILE);
        if (file.exists()) {
            Files.newOutputStream(path, TRUNCATE_EXISTING);
        }
    }

    @SneakyThrows
    public void fillTable() {
        File logDir = new File(PATH_LOGS);
        if (logDir.exists()) {
            fillListOfResultData();
        }
        TableColumn<ResultData, String> date = new TableColumn<>("Date");
        TableColumn<ResultData, String> time = new TableColumn<>("Time");
        TableColumn<ResultData, String> level = new TableColumn<>("Level");
        TableColumn<ResultData, String> codeRow = new TableColumn<>("Class:row");
        TableColumn<ResultData, String> expression = new TableColumn<ResultData, String>("Expression");
        TableColumn<ResultData, String> result = new TableColumn<ResultData, String>("Result");

        date.setCellValueFactory(new PropertyValueFactory<>("date"));
        time.setCellValueFactory(new PropertyValueFactory<>("time"));
        level.setCellValueFactory(new PropertyValueFactory<>("level"));
        codeRow.setCellValueFactory(new PropertyValueFactory<>("codeRow"));
        expression.setCellValueFactory(new PropertyValueFactory<>("expression"));
        result.setCellValueFactory(new PropertyValueFactory<>("result"));
        table.getColumns()
             .addAll(date, time, level, codeRow, expression, result);
        table.setItems(listOfResultData);
    }

    @SneakyThrows
    public void refreshTable() {
        fillListOfResultData();
        table.refresh();
    }


    @AllArgsConstructor
    @Getter
    public static class ResultData {
        private String date;
        private String time;
        private String level;
        private String codeRow;
        private String expression;
        private String result;
    }


}
