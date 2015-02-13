import java.util.*;
import java.io.*;
/**
 * Class that manipulates ingredients in arrays
 * @author Steve Juarez
 */
public class ListIngredient {
	
	private final int DEFAULT_MAX_INGREDIENTS = 100;
	
	/**
	 * array of ingredients
	 */
	private Ingredient[] ingredientList;
	
	/**
	 * number of ingredients
	 */
	private int numIngredients;
	
	/**
	 * Constructor that creates array of type ingredients
	 */
	public ListIngredient(){
		ingredientList = new Ingredient[DEFAULT_MAX_INGREDIENTS];
		numIngredients = 0;
	}
	
	/**
	 * Method to add ingredient to list
	 * @param name of ingredient
	 * @param calorieCount of ingredient
	 */
	public void add(String name, double calorieCount){
		Ingredient ingredient = new Ingredient(name, calorieCount);
		ingredientList[numIngredients] = ingredient;
		numIngredients++;
	}
	
	/**
	 * method to find an ingredient
	 * @param name of ingredient
	 * @return calorieCount of ingredient
	 */
	public double find(String name){	
		
		// if list is empty, return 0.0
		if (numIngredients == 0){
			return 0.0;
		}
		
		// search the list for the specified ingredient
		for (int i = 0; i < numIngredients; i ++)
			if (ingredientList[i].getName().equals(name))
				return ingredientList[i].getCalorieCount();
		
		return 0.0;
		}
	
	/**
	 * method to read list of ingredients from a text file
	 * @param fileName file name of text file to be read
	 * @throws Exception
	 * @author CS1027
	 */
	public void readList(String fileName) throws Exception {		  
		
		  // create object that controls file reading and opens the file
		  InStringFile reader = new InStringFile(fileName);
		  System.out.println("\nReading from file " + fileName + "\n");

		  // read data from file one line at a time
				  
		  String line;
		  StringTokenizer tokenizer;
		  String ingredientName;
		  double calorieCount;

		  do
		    {
		      line = (reader.read());
		      
		      // get ingredient and quantity information
		      // Note: it is assumed that each line of the disk file has
		            
		      tokenizer = new StringTokenizer(line);
		      ingredientName = tokenizer.nextToken();
		      calorieCount = Double.parseDouble(tokenizer.nextToken());
				  
		      // add ingredient to list
		      this.add(ingredientName, calorieCount);

		    }while (!reader.endOfFile()); 
				   
		  reader.close(); 
		}
	
	/**
	 * method to count calories of a recipe
	 * @param fileName name of file to be read
	 * @return totalCalorieCount total calorie count of recipe
	 */
	public double count(String fileName) throws Exception{
		
		//create totalCalorieCount variable to be returned
		double totalCalorieCount = 0.0;
		
		//read recipe list and calorie list
		this.readList(fileName);
		ListIngredient list = new ListIngredient();
		list.readList("table.dat.txt");
		
		//loop through both lists to find then calculate calories per 100 grams for ingredient
		for (int i = 0; i < numIngredients; i++){
				double totalCalories = (ingredientList[i].getCalorieCount()/100)*list.find(ingredientList[i].getName());
				totalCalorieCount = totalCalories+totalCalorieCount;
		}
		return totalCalorieCount;
	}
}