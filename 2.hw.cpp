// Assignment: Swift Programming Exercises on Loops, Conditions, and Collections
// -------------------------------------------------------------

import Foundation

// -------------------------------------------------------------
// Problem 1: FizzBuzz
// -------------------------------------------------------------
for i in 1...100 {
    if i % 3 == 0 && i % 5 == 0 {
        print("FizzBuzz")
    } else if i % 3 == 0 {
        print("Fizz")
    } else if i % 5 == 0 {
        print("Buzz")
    } else {
        print(i)
    }
}

// -------------------------------------------------------------
// Problem 2: Prime Numbers
// -------------------------------------------------------------
func isPrime(_ number: Int) -> Bool {
    if number < 2 { return false }
    for i in 2..<number {
        if number % i == 0 {
            return false
        }
    }
    return true
}

print("Prime numbers from 1 to 100:")
for i in 1...100 {
    if isPrime(i) {
        print(i, terminator: " ")
    }
}
print("\n")

// -------------------------------------------------------------
// Problem 3: Temperature Converter
// -------------------------------------------------------------
func celsiusToFahrenheit(_ c: Double) -> Double { return (c * 9/5) + 32 }
func celsiusToKelvin(_ c: Double) -> Double { return c + 273.15 }
func fahrenheitToCelsius(_ f: Double) -> Double { return (f - 32) * 5/9 }
func kelvinToCelsius(_ k: Double) -> Double { return k - 273.15 }

let inputTemp = 25.0
let inputUnit = "C" // change to "F" or "K"

print("Temperature Converter:")
if inputUnit == "C" {
    print("\(inputTemp)°C = \(celsiusToFahrenheit(inputTemp))°F")
    print("\(inputTemp)°C = \(celsiusToKelvin(inputTemp))K")
} else if inputUnit == "F" {
    let c = fahrenheitToCelsius(inputTemp)
    print("\(inputTemp)°F = \(c)°C")
    print("\(inputTemp)°F = \(celsiusToKelvin(c))K")
} else if inputUnit == "K" {
    let c = kelvinToCelsius(inputTemp)
    print("\(inputTemp)K = \(c)°C")
    print("\(inputTemp)K = \(celsiusToFahrenheit(c))°F")
}

// -------------------------------------------------------------
// Problem 4: Shopping List Manager
// -------------------------------------------------------------
var shoppingList: [String] = ["Milk", "Bread", "Eggs"]
print("Shopping List Manager:")
print("Current list: \(shoppingList)")
shoppingList.append("Cheese")
print("After adding Cheese: \(shoppingList)")
if let index = shoppingList.firstIndex(of: "Bread") {
    shoppingList.remove(at: index)
}
print("After removing Bread: \(shoppingList)")

// -------------------------------------------------------------
// Problem 5: Word Frequency Counter
// -------------------------------------------------------------
let sentence = "Swift is great and Swift is powerful"
let words = sentence.lowercased().components(separatedBy: CharacterSet.alphanumerics.inverted).filter { !$0.isEmpty }

var wordFrequency: [String: Int] = [:]
for word in words {
    wordFrequency[word, default: 0] += 1
}
print("Word frequencies:", wordFrequency)

// -------------------------------------------------------------
// Problem 6: Fibonacci Sequence
// -------------------------------------------------------------
func fibonacci(_ n: Int) -> [Int] {
    if n <= 0 { return [] }
    if n == 1 { return [0] }
    var sequence = [0, 1]
    while sequence.count < n {
        sequence.append(sequence[sequence.count - 1] + sequence[sequence.count - 2])
    }
    return sequence
}
print("Fibonacci(10):", fibonacci(10))

// -------------------------------------------------------------
// Problem 7: Grade Calculator
// -------------------------------------------------------------
let students = ["Alice": 90, "Bob": 75, "Charlie": 60, "Diana": 85]
let scores = Array(students.values)
let average = Double(scores.reduce(0, +)) / Double(scores.count)
let maxScore = scores.max() ?? 0
let minScore = scores.min() ?? 0

print("Average Score: \(average), Highest: \(maxScore), Lowest: \(minScore)")
for (name, score) in students {
    let status = Double(score) >= average ? "above average" : "below average"
    print("\(name): \(score) (\(status))")
}

// -------------------------------------------------------------
// Problem 8: Palindrome Checker
// -------------------------------------------------------------
func isPalindrome(_ text: String) -> Bool {
    let cleaned = text.lowercased().filter { $0.isLetter }
    return cleaned == String(cleaned.reversed())
}
print("Is 'Racecar' palindrome? \(isPalindrome("Racecar"))")

// -------------------------------------------------------------
// Problem 9: Simple Calculator
// -------------------------------------------------------------
func add(_ a: Double, _ b: Double) -> Double { return a + b }
func subtract(_ a: Double, _ b: Double) -> Double { return a - b }
func multiply(_ a: Double, _ b: Double) -> Double { return a * b }
func divide(_ a: Double, _ b: Double) -> Double? { return b == 0 ? nil : a / b }

let num1 = 10.0, num2 = 5.0
print("Calculator:")
print("Add: \(add(num1, num2))")
print("Subtract: \(subtract(num1, num2))")
print("Multiply: \(multiply(num1, num2))")
if let result = divide(num1, num2) {
    print("Divide: \(result)")
} else {
    print("Error: Division by zero")
}

// -------------------------------------------------------------
// Problem 10: Unique Characters
// -------------------------------------------------------------
func hasUniqueCharacters(_ text: String) -> Bool {
    var seen: Set<Character> = []
    for char in text {
        if seen.contains(char) {
            return false
        }
        seen.insert(char)
    }
    return true
}
print("Has 'Swift' unique characters? \(hasUniqueCharacters("Swift"))")
print("Has 'Hello' unique characters? \(hasUniqueCharacters("Hello"))")

