import wikipedia

topic_name = input("Topic: ")
number_of_lines = int(input("Lines: "))
results = wikipedia.search(topic_name)
if not results:
    print("Please enter a Valid Topic")
    exit()

print("-> Fetch Wikipedia Page (1)")
print("-> Extract Summary (2)")
print(f"-> Return exactly {number_of_lines} lines (3)")


choice = int(input("Choice: "))

if (choice == 1):
    page = wikipedia.page(results[0])
    print(page.title)
    print(page.url)
    print(page.summary)

elif(choice == 2):
    summary = wikipedia.summary(results[0])
    print(summary)
    
elif(choice == 3):
    summary = wikipedia.summary(results[0], sentences = number_of_lines)
    print(summary)