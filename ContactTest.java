package CS320MobileApplication;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class ContactTest {

	//Test case creating a valid Contact object.
    @Test
    public void testContactCreation() {
        Contact contact = new Contact("1234567890", "John", "Doe", "0123456789", "123 Main St");
        assertEquals("1234567890", contact.getContactId());
        assertEquals("John", contact.getFirstName());
        assertEquals("Doe", contact.getLastName());
        assertEquals("0123456789", contact.getPhone());
        assertEquals("123 Main St", contact.getAddress());
    }

    // Test case for invalid contact ID scenarios.
    @Test
    public void testContactInvalidId() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact(null, "John", "Doe", "0123456789", "123 Main St");
        });
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12345678901", "John", "Doe", "0123456789", "123 Main St");
        });
    }
    
    // Test case for invalid firstName scenarios.
    @Test
    public void testContactInvalidFirstName() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("1234567890", null, "Doe", "0123456789", "123 Main St");
        });
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("1234567890", "JohnJacobJingleheimer", "Doe", "0123456789", "123 Main St");
        });
    }
    
    // Test case for invalid lastName scenarios.
    @Test
    public void testContactInvalidLastName() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("1234567890", "John", null, "0123456789", "123 Main St");
        });
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("1234567890", "John", "DoeSmithJohnson", "0123456789", "123 Main St");
        });
    }

    // Test case for invalid phone scenarios.
    @Test
    public void testContactInvalidPhone() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("1234567890", "John", "Doe", null, "123 Main St");
        });
        assertThrows(IllegalArgumentException.class, () -> {
        	
        	// Less than 10 digits.
            new Contact("1234567890", "John", "Doe", "012345678", "123 Main St"); 
        });
        assertThrows(IllegalArgumentException.class, () -> {
        	
        	// More than 10 digits.
            new Contact("1234567890", "John", "Doe", "01234567890", "123 Main St"); 
        });
        assertThrows(IllegalArgumentException.class, () -> {
        	
        	// Non-numeric.
            new Contact("1234567890", "John", "Doe", "abcdefghij", "123 Main St"); 
        });
    }

    // Test case for invalid address scenarios.
    @Test
    public void testContactInvalidAddress() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("1234567890", "John", "Doe", "0123456789", null);
        });
        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("1234567890", "John", "Doe", "0123456789", "123 Main Street, SomeCity, SomeState, 1234567890");
        });
    }
}
