#include <iostream>
#include "Subject.h"
#include "Engine.h"

int main() {
    Subject subject;
    Wrapper wrapper1(&subject, &Subject::replace_word, { 
        {"text", ""}, 
        {"old_word", ""}, 
        {"new_word", ""} 
    });
    Wrapper wrapper2(&subject, &Subject::search_phrase, { 
        {"text", ""}, 
        {"phrase", ""} 
    });
    Wrapper wrapper3(&subject, &Subject::capitalize_words, { 
        {"text", ""} 
    });
    Wrapper wrapper4(&subject, &Subject::capitalize_sentences, { 
        {"text", ""} 
    });
    Wrapper wrapper5(&subject, &Subject::add_sentence_numbers, { 
        {"text", ""} 
    });

    Engine engine;

    engine.register_command(&wrapper1, "command1");
    engine.register_command(&wrapper2, "command2");
    engine.register_command(&wrapper3, "command3");
    engine.register_command(&wrapper4, "command4");
    engine.register_command(&wrapper5, "command5");

    std::cout << engine.execute("command1", { 
        {"text", "hello world"}, 
        {"old_word", "world"}, 
        {"new_word", "C++"} 
    }) << std::endl;
    std::cout << engine.execute("command2", { 
        {"text", "hello world"}, 
        {"phrase", "world"} 
    }) << std::endl;
    std::cout << engine.execute("command3", { 
        {"text", "hello world from c++"} 
    }) << std::endl;
    std::cout << engine.execute("command4", { 
        {"text", "hello world. this is a test."} 
    }) << std::endl;
    std::cout << engine.execute("command5", { 
        {"text", "hello world. this is a test."} 
    }) << std::endl;
    int tmp;
    std::cin >> tmp;
    return 0;
}
