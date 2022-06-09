grade(SC):- % print the grade.
    round(SC) =< 49, write('E'), nl.
grade(SC):- % 'nl' represent to 'newline'.
    round(SC) >= 50, round(SC) =< 59, write('D'), nl.
grade(SC):-
    round(SC) >= 60, round(SC) =< 62, write('C-'), nl.
grade(SC):-
    round(SC) >= 63, round(SC) =< 66, write('C'), nl.
grade(SC):-
    round(SC) >= 67, round(SC) =< 69, write('C+'), nl.
grade(SC):-
    round(SC) >= 70, round(SC) =< 72, write('B-'), nl.
grade(SC):-
    round(SC) >= 73, round(SC) =< 76, write('B'), nl.
grade(SC):-
    round(SC) >= 77, round(SC) =< 79, write('B+'), nl.
grade(SC):-
    round(SC) >= 80, round(SC) =< 84, write('A-'), nl.
grade(SC):-
    round(SC) >= 85, round(SC) =< 89, write('A'), nl.
grade(SC):-
    round(SC) >= 90, round(SC) =< 100, write('A+'), nl.
% ',' represent to 'and', ';' represent to 'or'.
print:-  % ':-' represent to 'if'
    SC is 0.1*90 + 0.1*84.5 + 0.1*117 + 0.3*60 + 0.4*66, % Calculate the score.
    write('1, 410021001, Alan '), write(SC), write(' '), grade(SC); % Print the data.
	SC is 0.1*85 + 0.1*49.5 + 0.1*80 + 0.3*57 + 0.4*64,
    write('2, 410021002, Bob '), write(SC), write(' '), grade(SC);
    SC is 0.1*90 + 0.1*110.5 + 0.1*117 + 0.3*68 + 0.4*62,
    write('3, 410021003, Carrie '), write(SC), write(' '), grade(SC);
    SC is 0.1*117 + 0.1*85 + 0.1*0 + 0.3*44 + 0.4*55,
    write('4, 410021004, David '), write(SC), write(' '), grade(SC);
    SC is 0.1*85 + 0.1*56 + 0.1*50 + 0.3*57 + 0.4*67,
    write('5, 410021005, Ethan '), write(SC), write(' '), grade(SC);
    SC is 0.1*90 + 0.1*65 + 0.1*65 + 0.3*72 + 0.4*66,
    write('6, 410021006, Frank '), write(SC), write(' '), grade(SC);
    SC is 0.1*117 + 0.1*110.5 + 0.1*65 + 0.3*69 + 0.4*43,
    write('7, 410021007, Gary '), write(SC), write(' '), grade(SC);
    SC is 0.1*117 + 0.1*65 + 0.1*50 + 0.3*43 + 0.4*54,
    write('8, 410021008, Helen '), write(SC), write(' '), grade(SC);
    SC is 0.1*63 + 0.1*59.5 + 0.1*50 + 0.3*51 + 0.4*75,
    write('9, 410021009, Igor '), write(SC), write(' '), grade(SC);
    SC is 0.1*117 + 0.1*110.5 + 0.1*117 + 0.3*53 + 0.4*75,
    write('10, 410021010, Jeff '), write(SC), write(' '), grade(SC).