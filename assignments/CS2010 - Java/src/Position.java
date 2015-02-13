
public class Position {

	private int x, y; //x and y coordinate of position

	/** creates Position with x and y coordinate */
	public Position(int x, int y)
	{
		this.x = x;
		this.y = y;
	}

	/** returns x coordinate of position */
	public int getX()
	{
		return this.x;
	}

	/** returns y coordinate of position */
	public int getY()
	{
		return this.y;
	}

	/** compares position to another position */
	public int compareTo(Position p)
	{
		//if this is greater than p return 1
		if (this.getX() > p.getX() && this.getY() == p.getY() || this.getY() > p.getY())
			return 1;
		//if these positions are equal return 0
		if (this.getX() == p.getX() && this.getY() == p.getY())
			return 0;
		//if this is less than p return -1
		else
			return -1;
	}
}
