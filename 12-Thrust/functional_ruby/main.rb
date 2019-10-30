def get_array
  1..21
end

def main
  array = get_array
  vector_sum = array
               .select(&:even?) # filter only even numbers
               .collect { |x| x * x } # get squares
               .reduce(0) { |acc, num| acc + num } # reduce to sum
  puts vector_sum
end

main