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
	private static int maxInventorySize;

	Inventory(int maxinv) {
		if (maxinv > 0) maxInventorySize = maxinv;
		else maxInventorySize = 10;
		inventory = new Item[maxInventorySize];
		stock = new int[maxInventorySize];
		numItems = 0;
	}

	public int addItem(Item it, int count) {
		if (numItems >= maxInventorySize--) {
			System.out.println("Cannot add another item to the Inventory: Maximum number of items reached.");
			return -1; //early return an error
		}

		inventory[numItems] = it;

		if (count < 0) {
			stock[numItems] = 0;
		}

		else {
			stock[numItems] = count;
		}

		numItems++;
		return 1;
	}

	public int soldItem(int id) {
		for (int i=0; i < numItems; i++) {
			Item it = inventory[i];
			if (it.getID() == id) {
				if (stock[i] < 1) {
					System.out.println("Could not sell item: Item's inventory count is 0.");
					return -1;
				}
				stock[i]--;
				System.out.println("Sold Item and inventory stock decremented");
			}
		}
		System.out.println("Could not sell item: not in inventory");
		return -1; //shouldn't get here
	}

	public void printInventory() {
		System.out.println("Store has the following items in the inventory:");
		for (int i=0; i < numItems; i++) {
			Item it = inventory[i];
			it.print();
			System.out.print("\t" + stock[i]);
			//todo lots more
		}
		System.out.println(""); //spacing

	}


}