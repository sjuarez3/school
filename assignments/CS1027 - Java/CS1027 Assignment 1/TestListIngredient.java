import java.io.*;
/**
 * Class to test Ingredient and ListIngredient methods
 * @author Steve
 */
public class TestListIngredient {
	
	  public static void main(String[] args) throws Exception{

		String database = "table.dat.txt";
	    String recipe = "pasta.txt";
	    ListIngredient calorieList = new ListIngredient();
	    calorieList.readList(database);
	    
	    //prints calorie count for butter
	    System.out.println(calorieList.find("butter"));
	    
	    ListIngredient pasta = new ListIngredient();
	    
	    //prints total calorie count of recipe
	    System.out.println(pasta.count(recipe));
	  }
	}
