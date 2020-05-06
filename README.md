# slang
A very simple language that was made just to be made

Example syntax:
# Syntax
people = 5;

    read_name = { :(msg_to_print)
        p(msg_to_print)
        return get() // return not necessery, last _ will always be returned
    }

    for(i = 0, i < people, i = i + 1, {
        name = read_name("Enter your name: ");
        pln("Hello there, %s!", name);

        p("Now enter your age: ");
        age = get();
        if(age < 18, {
            pln("You can't drink alcochol!");
        }, {
            pln("You can drink alcochol!!");
        });
    });
