
public class DictEntry {

	private int color; 	//color of pixel
	private Position p; //position of pixel

	/** creates dictionary entry with position and color */
	public DictEntry(Position p, int color)
	{
		this.p = p;
		this.color = color;
	}

	/** returns position of this entry */
	public Position getPosition()
	{
		return this.p;
	}

	/** returns color of this entry */
	public int getColor()
	{
		return this.color;
	}
}
