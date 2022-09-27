import re

def inputData():
    data = []

    recipeRegex = re.compile(r'(.+) \(contains (.+)\)')
    try:
        while True:
            line = input()
            match = recipeRegex.fullmatch(line)
            assert(match != None)
            recipe, allergens = match.groups()
            ingredients = recipe.split(' ')
            allergens = allergens.split(', ')
            data.append((ingredients, allergens))
    except EOFError:
        pass

    return data

def getAllAllergens(recipes):
    return  set(allergen for _, allergens in recipes for allergen in allergens)

def getAllIngredients(recipes):
    return set(ingredient for ingredients, _ in recipes for ingredient in ingredients)

def getAllergenSets(recipes):
    allergenSets = {}
    allAllergens = getAllAllergens(recipes)
    allIngredients = getAllIngredients(recipes)
    for allergen in allAllergens:
        allergenSets[allergen] = allIngredients

    for ingredients, allergens in recipes:
        for allergen in allergens:
            allergenSets[allergen] = allergenSets[allergen].intersection(ingredients)
    
    return allergenSets

def part1(recipes):
    # allIngredients = getAllIngredients(recipes)
    allergenSets = getAllergenSets(recipes)
    allPossibleAllergenics = set(allergen for allergenSet in allergenSets.values() for allergen in allergenSet)
    # nonAllergenic = allIngredients - allPossibleAllergenics
    s = 0
    for ingredients, _ in recipes:
        for ingredient in ingredients:
            if allPossibleAllergenics.isdisjoint(set([ingredient])):
                s+= 1
    return s

def findMatchingAllergens(allergenSets: dict, mappedIngredients: dict):
    if len(mappedIngredients) == len(allergenSets):
        return True
    for allergen, ingredients in allergenSets.items():
        unmapped = [x for x in ingredients if mappedIngredients.get(x, None) == None]
        if len(unmapped) == 1:
            ingredient, = unmapped
            mappedIngredients[ingredient] = allergen
            if findMatchingAllergens(allergenSets, mappedIngredients):
                return True
            mappedIngredients.pop(ingredient)
            return False
    
    for allergen, ingredients in allergenSets.items():
        unmapped = [x for x in ingredients if mappedIngredients.get(x, None) == None]
        if len(unmapped) > 1:
            ingredient, = unmapped
            mappedIngredients[ingredient] = allergen
            if findMatchingAllergens(allergenSets, mappedIngredients):
                return True
            mappedIngredients[ingredient] = None
    return False

def part2(recipes):
    allergenSets = getAllergenSets(recipes)

    mappedIngredients = {}
    findMatchingAllergens(allergenSets, mappedIngredients)
    
    sortedItems = sorted(mappedIngredients.items(), key = lambda x: x[1])
    return ','.join(x for x, _ in sortedItems)

def main():
    data = inputData()
    print("1)", part1(data))
    print("2)", part2(data))

if __name__ == "__main__":
    main()