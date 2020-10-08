/**
 * @author Dawson Dauphinais
 * <p>
 * Date last modified: 2/19/2018
 * <p>
 * CS 1122 Spring 2018
 * <p>
 * In-Class Web Browser Assignment
 */

import javafx.application.Application;
import javafx.concurrent.Worker;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.web.WebEngine;
import javafx.scene.web.WebView;
import javafx.stage.Stage;
import javafx.geometry.Insets;


public class WebBrowser extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        BorderPane pane = new BorderPane();
        Scene scene = new Scene(pane);

        // Statusbar on bottom
        HBox statusBarArea = new HBox(10);
        statusBarArea.setPadding(new Insets(10));
        Label statusBar = new Label();
        statusBarArea.getChildren().addAll(statusBar);
        pane.setBottom(statusBarArea);

        // Web page in center
        WebView view = new WebView();
        WebEngine engine = view.getEngine();
        engine.load("http://google.com");
        engine.setOnStatusChanged(event -> {
            statusBar.setText(event.getData());
        });
        pane.setCenter(view);

        // Toolbar on top
        HBox toolBarArea = new HBox(10);
        toolBarArea.setPadding(new Insets(10));
        Button backButton = new Button("<");
        backButton.setOnAction(event -> {
            if (engine.getHistory().getCurrentIndex() > 0) {
                engine.getHistory().go(-1);
            }

        });

        Button nextButton = new Button(">");
        nextButton.setOnAction(event -> {
            if (engine.getHistory().getCurrentIndex() < engine.getHistory().getEntries().size()) {
                engine.getHistory().go(1);
            }

        });

        Button helpButton = new Button("?");
        helpButton.setOnAction(event -> {
            engine.load("C://Users//Dawson//Documents//School Stuff//CS1121//Homework//Week5Notes.java//src//help.html");
        });

        TextField urlEntry = new TextField();
        urlEntry.setOnAction(event -> {
            String url = urlEntry.getText();
            if (!(url.startsWith("http://") || url.startsWith("https://"))) {
                url = "http://" + url;
            }
            engine.load(url);
        });


        toolBarArea.getChildren().addAll(backButton, nextButton, urlEntry, helpButton);
        toolBarArea.setHgrow(urlEntry, Priority.ALWAYS);
        pane.setTop(toolBarArea);

        engine.getLoadWorker().stateProperty().addListener(
                (ov, oldState, newState) -> {
                    if (newState == Worker.State.SUCCEEDED) {
                        //primaryStage.setTitle(engine.getLocation());
                        urlEntry.setText(engine.getLocation());
                    }
                }
        );


        primaryStage.titleProperty().bind(engine.titleProperty());

        primaryStage.setScene(scene);
        primaryStage.show();

    }

}
