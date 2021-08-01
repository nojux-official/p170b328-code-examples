use std::thread;
use std::thread::JoinHandle;

/** Writes some simple output to console output
param name: thread's name, printed in each output line
*/
fn execute(name: &str) {
    println!("{}", name.to_owned() + ": one");
    println!("{}", name.to_owned() + ": two");
    println!("{}", name.to_owned() + ": three");
}


fn main() {
    // create names for threads
    let names = vec!["First", "Second"];
    let threads: Vec<JoinHandle<_>> = names
        .iter()
        // for each name create a thread and return its join handle
        .map(|name| {
            // to_owned is required because Rust will not allow accessing variables from multiple
            // threads
            let owned_name = name.to_owned();
            thread::spawn(move || execute(owned_name))
        }).collect();
    threads
        .into_iter()
        // for each join handle call join and unwrap. join returns a result (join success or
        // failure), unwrap calls either discards success or panics on error
        .for_each(|t| t.join().unwrap());
    println!("Program finished execution.");
}
