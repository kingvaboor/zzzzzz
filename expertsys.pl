% Declare has_symptom/2 as dynamic
:- dynamic has_symptom/2.

% Facts: Define symptoms associated with diseases
symptom(flu, fever).
symptom(flu, cough).
symptom(flu, body_ache).

symptom(cold, sneezing).
symptom(cold, runny_nose).
symptom(cold, sore_throat).

symptom(measles, fever).
symptom(measles, rash).
symptom(measles, conjunctivitis).

% Rules: If certain symptoms are present, infer a disease
disease(Patient, flu) :-
    has_symptom(Patient, fever),
    has_symptom(Patient, cough),
    has_symptom(Patient, body_ache).

disease(Patient, cold) :-
    has_symptom(Patient, sneezing),
    has_symptom(Patient, runny_nose),
    has_symptom(Patient, sore_throat).

disease(Patient, measles) :-
    has_symptom(Patient, fever),
    has_symptom(Patient, rash),
    has_symptom(Patient, conjunctivitis).

% Ask the user about symptoms
ask(Patient, Symptom) :-
    format('Does ~w have ~w? (yes/no): ', [Patient, Symptom]),
    read(Reply),
    (Reply == yes -> assert(has_symptom(Patient, Symptom)) ; true).

% Diagnose a disease based on symptoms
diagnose(Patient) :-
    write('Diagnosing disease for '), write(Patient), nl,
    ask(Patient, fever),
    ask(Patient, cough),
    ask(Patient, body_ache),
    ask(Patient, sneezing),
    ask(Patient, runny_nose),
    ask(Patient, sore_throat),
    ask(Patient, rash),
    ask(Patient, conjunctivitis),
    (disease(Patient, Disease) ->
        format('~w probably has ~w.', [Patient, Disease])
    ;   write('No diagnosis could be made.')).

% Sample test case to run the diagnosis for a patient 'john'
run_diagnosis :-
    diagnose(john).
