### To run Apex file without vfp

Marksheet m = new Marksheet();

Map<String,Integer>marks = new Map<String,Integer>{
    'English' => 88,
    'Maths' => 100,
    'Science' => 95,
    'Economics' => 88,
    'Computers' => 100
};

m.calculate_result(marks);

Paste the above in execute anonymous window
