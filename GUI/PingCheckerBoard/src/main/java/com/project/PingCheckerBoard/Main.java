package com.project.PingCheckerBoard;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
 
public class Main extends Application {
	public static BoardGUI boardGUI;
	public static BorderPane borderPane;
	public static Stage stage;
	
    public static void main(String[] args) {
        launch(args);
    }
    
    @Override
    public void start(Stage stage) {
    	Main.stage = stage;
    	Main.stage.setTitle("Ping Checker Board");
        
        borderPane = new BorderPane();
        Main.stage.setScene(new Scene(borderPane));
        Main.stage.show();
        
        boardGUI = new BoardGUI(2, 9);
        borderPane.setCenter(boardGUI);
        
        ControlPane controlPane = new ControlPane();
        borderPane.setRight(controlPane);
    }
}