

import Foundation

// MARK: - Product (struct)
struct Product {
    let id: String
    let name: String
    let price: Double
    let category: Category
    let description: String
    
    // Категории продукта
    enum Category {
        case electronics, clothing, food, books
    }
    
    // Отображаемая цена (формат)
    var displayPrice: String {
        String(format: "$%.2f", price)
    }
    
    // Инициализатор с валидацией цены (failable)
    init?(id: String = UUID().uuidString,
          name: String,
          price: Double,
          category: Category,
          description: String = "") {
        guard price > 0 else { return nil } // цена должна быть положительной
        self.id = id
        self.name = name
        self.price = price
        self.category = category
        self.description = description
    }
}

// MARK: - CartItem (struct)
//
// CartItem — value type (struct). Хранит продукт и количество.
// Поддерживает mutating методы для изменения количества.
struct CartItem {
    let product: Product
    private(set) var quantity: Int
    
    // Subtotal = price * quantity
    var subtotal: Double {
        product.price * Double(quantity)
    }
    
    // Инициализатор с валидацией количества
    init(product: Product, quantity: Int = 1) {
        self.product = product
        self.quantity = max(1, quantity) // если передали <=0, ставим 1
    }
    
    // Обновить количество (mutating)
    mutating func updateQuantity(_ newQuantity: Int) {
        guard newQuantity > 0 else { return }
        quantity = newQuantity
    }
    
    // Увеличить количество на amount (mutating)
    mutating func increaseQuantity(by amount: Int) {
        guard amount > 0 else { return }
        quantity += amount
    }
}

// MARK: - ShoppingCart (class)
class ShoppingCart {
    private(set) var items: [CartItem] = []
    var discountCode: String?
    
    init() {}
    
    // Добавить товар в корзину. Если уже есть — увеличить количество.
    func addItem(product: Product, quantity: Int = 1) {
        guard quantity > 0 else { return }
        
        if let index = items.firstIndex(where: { $0.product.id == product.id }) {
            // mutating на элемент массива
            items[index].increaseQuantity(by: quantity)
        } else {
            let newItem = CartItem(product: product, quantity: quantity)
            items.append(newItem)
        }
    }
    
    // Удалить товар по ID
    func removeItem(productId: String) {
        items.removeAll { $0.product.id == productId }
    }
    
    // Обновить количество (если 0 — удалить)
    func updateItemQuantity(productId: String, quantity: Int) {
        guard let index = items.firstIndex(where: { $0.product.id == productId }) else { return }
        if quantity <= 0 {
            removeItem(productId: productId)
        } else {
            items[index].updateQuantity(quantity)
        }
    }
    
    // Очистить корзину
    func clearCart() {
        items.removeAll()
    }
    
    // Вычисляемые свойства
    var subtotal: Double {
        items.reduce(0) { $0 + $1.subtotal }
    }
    
    // Простая система скидок по коду
    var discountAmount: Double {
        guard let code = discountCode else { return 0 }
        switch code {
        case "SAVE10":
            return subtotal * 0.10
        case "SAVE20":
            return subtotal * 0.20
        default:
            return 0
        }
    }
    
    var total: Double {
        max(0, subtotal - discountAmount)
    }
    
    var itemCount: Int {
        items.reduce(0) { $0 + $1.quantity }
    }
    
    var isEmpty: Bool {
        items.isEmpty
    }
}

// MARK: - Address (struct)
struct Address {
    let street: String
    let city: String
    let zipCode: String
    let country: String
    
    var formattedAddress: String {
        "\(street)\n\(city), \(zipCode)\n\(country)"
    }
}

// MARK: - Order (struct)

struct Order {
    let orderId: String
    let items: [CartItem]
    let subtotal: Double
    let discountAmount: Double
    let total: Double
    let timestamp: Date
    let shippingAddress: Address
    
    init(from cart: ShoppingCart, shippingAddress: Address) {
        self.orderId = UUID().uuidString
        self.items = cart.items // копируется как value
        self.subtotal = cart.subtotal
        self.discountAmount = cart.discountAmount
        self.total = cart.total
        self.timestamp = Date()
        self.shippingAddress = shippingAddress
    }
    
    var itemCount: Int {
        items.reduce(0) { $0 + $1.quantity }
    }
}

// MARK: - (Optional) User class (bonus)

class User {
    let userId: String
    let name: String
    let email: String
    private(set) var orderHistory: [Order] = []
    
    init(userId: String = UUID().uuidString, name: String, email: String) {
        self.userId = userId
        self.name = name
        self.email = email
    }
    
    func placeOrder(_ order: Order) {
        orderHistory.append(order)
    }
    
    var totalSpent: Double {
        orderHistory.reduce(0) { $0 + $1.total }
    }
}

// MARK: - Тестовые сценарии


print("=== Тестовые сценарии: ShoppingCartAssignment ===\n")


guard let laptop = Product(name: "Laptop", price: 1200.00, category: .electronics, description: "High performance laptop"),
      let book = Product(name: "Swift Book", price: 40.00, category: .books, description: "Learn Swift programming"),
      let headphones = Product(name: "Headphones", price: 80.00, category: .electronics, description: "Noise cancelling headphones") else {
    fatalError("Не удалось создать продукты (валидация цены)")
}

print("Продукты созданы:")
print(" - \(laptop.name): \(laptop.displayPrice)")
print(" - \(book.name): \(book.displayPrice)")
print(" - \(headphones.name): \(headphones.displayPrice)\n")


let cart = ShoppingCart()
cart.addItem(product: laptop, quantity: 1)
cart.addItem(product: book, quantity: 2)

print("После добавления laptop x1 и book x2:")
print("Subtotal: \(cart.subtotal)")
print("Item count: \(cart.itemCount)\n")


cart.addItem(product: laptop, quantity: 1) // laptop теперь x2
if let laptopItem = cart.items.first(where: { $0.product.id == laptop.id }) {
    print("Laptop quantity после добавления ещё 1: \(laptopItem.quantity) (ожидается 2)")
}
print()


print("Подытог корзины (subtotal): \(cart.subtotal)")
print("Количество предметов (itemCount): \(cart.itemCount)\n")


cart.discountCode = "SAVE10"
print("Discount code: \(cart.discountCode ?? "nil")")
print("Discount amount: \(cart.discountAmount)")
print("Total с учётом скидки: \(cart.total)\n")


cart.removeItem(productId: book.id)
print("После удаления книги:")
print("Subtotal: \(cart.subtotal)")
print("Item count: \(cart.itemCount)\n")


func modifyCart(_ c: ShoppingCart) {
    c.addItem(product: headphones, quantity: 1)
}
modifyCart(cart)

print("После внешнего вызова modifyCart(cart):")
print("Cart item count: \(cart.itemCount) (ожидается увеличено)\n")


let item1 = CartItem(product: laptop, quantity: 1)
var item2 = item1
item2.updateQuantity(5)
print("Value-type демонстрация:")
print("item1.quantity = \(item1.quantity) (ожидается 1)")
print("item2.quantity = \(item2.quantity) (ожидается 5)\n")


let address = Address(street: "123 Main St", city: "Almaty", zipCode: "050000", country: "Kazakhstan")
let order = Order(from: cart, shippingAddress: address)
print("Order создан с id: \(order.orderId)")
print("Order subtotal: \(order.subtotal), total: \(order.total), itemCount: \(order.itemCount)\n")


cart.clearCart()
print("После очистки корзины:")
print("Cart item count: \(cart.itemCount) (ожидается 0)")
print("Order item count: \(order.itemCount) (ожидается значение до очистки корзины)\n")

let user = User(name: "Sasha", email: "sasha@example.com")
user.placeOrder(order)
print("Пользователь \(user.name) разместил 1 заказ. История заказов: \(user.orderHistory.count)")
print("Total spent by user: \(user.totalSpent)\n")

print("=== Тесты завершены ===")
