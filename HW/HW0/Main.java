
/**
 * Main class to test hw0 classes
 * Other classes include: Item and Inventory that students should implement
 *
 * CS 305, Fall 2019
 * @author Martin Cenek
 * @version August 2019
 */
public class Main {
    public static void main(String[] args) {
        // create Stores with Inventories
        Inventory rei = new Inventory(-3);  //should create an rei store with the default inventory size of 10 items
        Inventory amazon = new Inventory(20);

        // create items
        Item gloves = new Item(10.25, "WarmFingers", 1);
        Item hat = new Item(5.75, "WarmEars", 2);
        Item boots = new Item(35.22, "KeepOnStomping", 3);
        Item skateboard = new Item(67.04, "PlankOnWheels", 4);
        Item skis = new Item(352.00, "QuickPlanks", 5);
        Item tent = new Item(223.47, "Fortress007", 6);
        Item slBag = new Item(125.17, "WarmDreams", 7);
        Item slPad = new Item(63.58, "SoftDreams", 8);
        Item canoe = new Item(458.46, "QuickDownTheRiver", 9);
        Item stove = new Item(25.14, "Burn Hot", 10);
        Item mug = new Item(8.25, "Big brown mug", 11);
        Item backpack = new Item(125.54, "Heavy sturdy backpack", 12);

        // put some items into the rei store
        rei.addItem(gloves, 10);
        rei.addItem(hat, 2);
        rei.addItem(boots, -1);
        rei.addItem(skateboard, 0);

        // for write-up: draw a picture of what rei's store has in its inventory (object view)

        // print rei's inventory
        rei.printInventory();

        // put more items into rei's inventory
        rei.addItem(skis,5);
        rei.addItem(tent,2);
        rei.addItem(slBag,10);
        rei.addItem(slPad,12);

        // print rei's inventory
        rei.printInventory();

        // add items
        rei.addItem(canoe, 4);
        rei.addItem(stove, 6);

        // print rei's inventory
        rei.printInventory();

        // add items
        rei.addItem(mug,7);
        rei.addItem(backpack,3);

        // print rei's inventory
        rei.printInventory();

        // sell items from rei store
        rei.soldItem(2);
        rei.soldItem(5);
        // print rei's inventory
        rei.printInventory();
        // sell items from rei store
        rei.soldItem(2);
        rei.soldItem(2);
        rei.soldItem(2);
        // print rei's inventory
        rei.printInventory();

        rei.soldItem(13);

        // add items to amazon store
        amazon.addItem(tent, 5);
        amazon.addItem(skis,10);
        amazon.printInventory();

        // add another item
        amazon.addItem(canoe, 4);

        // for write-up
        //System.out.println(rei);
        //System.out.println(amazon);

        return;
    }
}
