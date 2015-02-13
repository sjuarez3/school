/**
 * Class for identifying ingredients by name and calorie count
 * @author Steve Juarez
 */
public class Ingredient {
	
	/**
	 * name of ingredient
	 */
	private String name;
	
	/**
	 * calorie count of ingredient
	 */
	private double calorieCount;
	
	/**
	 * Constructor creates object with given name and calorie count
	 * @param name of ingredient
	 * @param calorieCount of ingredient
	 */
	public Ingredient(String name, double calorieCount){
		this.name = name;
		this.calorieCount = calorieCount;	
	}
	
	/**
	 * method to return name of ingredient
	 * @return name of ingredient of type string
	 */
	public String getName(){
		return this.name;
	}
	
	/**
	 * method to return calorie count of ingredient
	 * @return calorieCount of ingredient
	 */
	public double getCalorieCount(){
		return this.calorieCount;
	}
}