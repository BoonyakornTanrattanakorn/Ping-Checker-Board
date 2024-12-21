package com.project.PingCheckerBoard;

import javafx.geometry.Insets;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;

public class ControlPane extends GridPane {
	private TextField rowInput, colInput;
	private Text warningText;
	
	public ControlPane() {
		setPadding(new Insets(20));
		
		rowInput = new TextField();
		rowInput.setPromptText("input rows");
		colInput = new TextField();
		colInput.setPromptText("input columns");
		
		warningText = new Text("OK!");
		
		Button resetBoard = new Button("reset board");
		resetBoard.setOnAction(e->resetBoard());
		
		Button addRow = new Button("add row");
		addRow.setOnAction(e->Main.boardGUI.addRow());
		
		add(new Text("Row: "), 0, 0);
		add(rowInput, 1, 0);
		add(new Text("Column: "), 0, 1);
		add(colInput, 1, 1);
		add(warningText, 0, 2, 2, 1);
		add(resetBoard, 0, 3);
		add(addRow, 1, 3);
	}
	
	private void resetBoard() {
		int row, col;
		try {
			row = Integer.parseInt(rowInput.getText());
		} catch (NumberFormatException e){
			warningText.setText("Row is in wrong format!");
			warningText.setFill(Color.RED);
			return;
		}
		
		try {
			col = Integer.parseInt(colInput.getText());
		} catch (NumberFormatException e){
			warningText.setText("Column is in wrong format!");
			warningText.setFill(Color.RED);
			return;
		}
		
		Main.boardGUI = new BoardGUI(row, col);
		Main.borderPane.setCenter(Main.boardGUI);
		warningText.setText("OK!");
		warningText.setFill(Color.BLACK);
	}
}
