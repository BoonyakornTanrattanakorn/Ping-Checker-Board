package com.project.PingCheckerBoard;

import javafx.geometry.Pos;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;

public class BoardGUI extends GridPane {
    private static double TILE_SIZE;
    private static final double MAX_TILE_SIZE = 100;
    private static final int EXTEND_ROW = 5;
    private int rows, cols;
    

    public BoardGUI(int rows, int cols) {
    	TILE_SIZE = Math.min(Main.stage.getHeight()/rows, Main.stage.getWidth()/cols);
    	TILE_SIZE = Math.min(MAX_TILE_SIZE, TILE_SIZE);
    	
        setAlignment(Pos.CENTER);

        this.rows = rows;
        this.cols = cols;
        
        initializeTiles();
        initializePieces();
    }
    
    private void initializeTiles() {
    	for(int i = 0; i < rows+EXTEND_ROW; ++i) {
    		for(int j = 0; j < cols; ++j) {
    			Rectangle tile = new Rectangle(TILE_SIZE, TILE_SIZE);
    			tile.setFill((i + j) % 2 == 0 ? Color.BEIGE : Color.BROWN);
    			add(tile, j, i);
    		}
    	}
    }
    
    private void initializePieces() {
    	for(int i = 0; i < rows; ++i) {
    		for(int j = 0; j < cols; ++j) {
    			createPiece(j, i);
    		}
    	}
    }
    
    private void createPiece(int i, int j) {
    	Circle piece = new Circle(TILE_SIZE/3);
    	piece.setStroke(Color.BLACK);
    	
        final double[] offset = new double[2];

        // Enable dragging
        piece.setOnMousePressed(event -> {
            offset[0] = event.getSceneX() - piece.getTranslateX();
            offset[1] = event.getSceneY() - piece.getTranslateY();
        });

        piece.setOnMouseDragged(event -> {
            piece.setTranslateX(event.getSceneX() - offset[0]);
            piece.setTranslateY(event.getSceneY() - offset[1]);
        });
        
        piece.setTranslateX(TILE_SIZE/6);
    	
    	add(piece, i, j);
    }
    
    public void addRow() {
    	for(int j = 0; j < cols; ++j) {
			Rectangle tile = new Rectangle(TILE_SIZE, TILE_SIZE);
			tile.setFill((rows+j) % 2 == 0 ? Color.BEIGE : Color.BROWN);
			add(tile, j, rows);
    	}
    	++rows;
    }
}
