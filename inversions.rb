require 'pp'

file = ARGV[0]

arr = []

File.open(file).each do |line|
  arr << line.to_i
end

def sort_and_count(arr)
  return [0,arr] if arr.length <= 1

  midpoint = arr.length/2

  left = arr[0...midpoint]
  right = arr[midpoint..arr.length]

  l_count,left = sort_and_count(left)
  r_count,right = sort_and_count(right)
  s_count,merged = merge_and_count(left, right)

  return [l_count+r_count+s_count, merged]
end

def merge_and_count(left, right)
  arr = []
  length = left.length + right.length
  j = k = inversions = 0

  (0...length).each do
    if left.first <= right.first
      arr << left.shift
      if left.length == 0
        arr += right
        break
      end
    else
      arr << right.shift
      inversions += left.length

      if right.length == 0
        arr += left
        break
      end
    end
  end

  [inversions, arr]
end

count, sorted = sort_and_count(arr)

puts "inversions: #{count}"
