/**
 * Inventory class
 * Interacts with: Item, Main
 * CS 305, Fall 2019
 * @author Kai Richardson
 * @version September 2019
 */
public class Inventory {
	//declare vars
	private Item[] inventory;
	private int[] stock;
	private int numItems;
	private static int maxInventorySize = 10;

	Inventory(int maxinv) {
		if (maxinv > 0) maxInventorySize = maxinv;
		inventory = new Item[maxInventorySize];
		stock = new int[maxInventorySize];
	}

	public int addItem(Item it, int count) {
		if (numItems >= maxInventorySize) {
			System.out.println("Cannot add another item to the Inventory: Maximum number of items reached.");
			return -1; //early return an error
		}

		if (count <= 0) {
			//set the item's stock count in the stock array to 0
			inventory[it.getID()] = it;
			stock[it.getID()] = 0;
			numItems--;
			return 0;
		}

		else {
			//set it the count passed in
			inventory[it.getID()] = it;
			stock[it.getID()] = count;
			numItems++;
			return 1;
		}
	}

	public int soldItem(int id) {
		for (int i=0; i < maxInventorySize; i++) {
			Item it = inventory[i];
			if (it == null) return -1;
			if (it.getID() == id) {
				if (stock[id] < 1) {
					System.out.println("Could not sell item: Item's inventory count is 0.");
					return -1;
				}
				stock[id]--;
				System.out.println("Sold Item and inventory stock decremented");
			}
		}
		System.out.println("Could not sell item: not in inventory");
		return -1; //shouldn't get here
	}

	public void printInventory() {
		System.out.println("Store has the following items in the inventory:");
		for (int i=0; i < maxInventorySize; i++) {
			Item it = inventory[i];
			if (it == null) return;
			it.print();
			System.out.print(" " + stock[it.getID()]);
			//todo lots more
		}

	}


}