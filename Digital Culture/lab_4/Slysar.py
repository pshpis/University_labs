def dist(str1, str2):
    if len(str1) > len(str2):
        str1, str2 = str2, str1

    n = len(str1)
    m = len(str2)

    editor = range(n + 1)
    for i in range(1, m + 1):
        prev = editor
        editor = [i] + [0] * n
        for j in range(1, n + 1):
            add = prev[j] + 1
            delete = editor[j - 1] + 1
            change = prev[j - 1]
            if str1[j - 1] != str2[i - 1]:
                change += 1
            editor[j] = min(add, delete, change)
    return editor[n]


# Text reading
text = open(' text.txt', "r", encoding="utf-8").read().lower()
punctuation = "!?,;.:—«()»"
text = "".join([ch for ch in text if ch not in punctuation])
text_list = text.split()

# Dictionary reading
dictionary_text_list = open('dict1.txt', "r", encoding="utf-8").read().lower().split()
dictionary = list([dictionary_text_list[i] for i in range(0, len(dictionary_text_list), 2)])

dictionary_frequency = {}
for i in range(0, len(dictionary_text_list), 2):
    dictionary_frequency.update({dictionary_text_list[i]: int(dictionary_text_list[i + 1])})
dictionary_frequency.update({"": -1})

text_list_frequency = {}
for word in text_list:
    if text_list_frequency.get(word) is not None:
        text_list_frequency.update({word: text_list_frequency.get(word) + 1})
    else:
        text_list_frequency.update({word: 1})

good_words_counter = 0
words_not_from_dict = []
for word in text_list:
    if word in dictionary:
        good_words_counter += 1
    else:
        words_not_from_dict.append(word)


for word in words_not_from_dict:
    min_word_dist = len(word)
    correct_word = ""
    for dict_word in dictionary:
        if dist(word, dict_word) < min_word_dist:
            min_word_dist = dist(word, dict_word)
            correct_word = dict_word

        if dist(word, dict_word) == min_word_dist \
                and dictionary_frequency[dict_word] > dictionary_frequency[correct_word]:
            min_word_dist = dist(word, dict_word)
            correct_word = dict_word

    if min_word_dist > 2:
        for words_counter in range(len(word)):
            if word[:words_counter] in dictionary and word[words_counter:] in dictionary:
                print(word + ' ' + word[:words_counter] + ' ' + word[words_counter:] + ' ' + str(1))
    else:
        print(word + ' ' + correct_word + ' ' + str(min_word_dist))


print("Чило словоформ в словаре из текста - ", good_words_counter)
print("Число словоформ - ", len(text_list))
print("Число уникальных слово форм - ", len(text_list_frequency))
