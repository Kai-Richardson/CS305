/**
 * Item class
 * Interacts with: Inventory, Main
 */
public class Item {
	private double price;
	private String name;
	private int ID; //fullcaps should be reserved for compiler defines/consts, imo

	Item(double price, String name, int ID) {
		this.price = price;
		this.name = name;
		this.ID = ID;
	}

	public void print() {
		System.out.print("Item" + getPrice() + "\t" + name + "\t" + getID())
	}

	public double getPrice() {
		return this.price;
	}

	public int getID() {
		return this.ID;
	}
}