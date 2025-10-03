// Assignment: My Life Story in Swift

import Foundation

// Step 1: Personal Information
let firstName: String = "Zhuziya"
let lastName: String = "Puzya"
let birthYear: Isnt = 2005
let currentYear: Int = 2025
let age: Int = currentYear - birthYear
let isStudent: Bool = true
let height: Double = 1.70
let country: String = "Kazakhstan"

// Step 2: Hobbies and Interests
let hobby: String = "Reading, horsing, listening to music and work"
let numberOfHobbies: Int = 4
let favoriteNumber: Int = 7
let favoriteFood: String = "Pasta"
let favoriteEmoji: String = "📚"
let isHobbyCreative: Bool = true

// Step 3: Life Story Summary
var lifeStory: String = """
My name is \(firstName) \(lastName). I am \(age) years old, born in \(birthYear).
I am currently a student. I live in \(country) and my height is \(height) meters.
My favorite hobby is \(hobby) \(favoriteEmoji), which is a creative hobby: \(isHobbyCreative).
I have \(numberOfHobbies) hobbies in total, and my favorite number is \(favoriteNumber).
I also enjoy eating \(favoriteFood).
"""

// Bonus Task: Future Goals
let futureGoals: String = "In the future, I want to become a successful analyst and travel the world."
lifeStory += " " + futureGoals

// Step 4: Print the Life Story
print(lifeStory)
