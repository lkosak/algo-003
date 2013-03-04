function quicksort(arr, left, right) {
  if(left < right) {
    var pivot = choosePivot(arr);

    var newIndex = partition(arr, left, right, pivot);

    quicksort(arr, left, newIndex-1);
    quicksort(arr, newIndex+1, right);
  }
}

function partition(arr, left, right, pivotIndex) {
  if(pivotIndex !== left) {
    swap(arr, left, pivotIndex);
  }

  var pivot = arr[left];
  var middle = left+1;

  for(var i=left+1; i<right; i++) {
    if(arr[i] < pivot) {
      swap(arr, i, middle);
      middle++;
    }
  }

  swap(arr, left, middle);
  return middle;
}

function swap(arr, first, second) {
  var temp = arr[first];
  arr[first] = arr[second];
  arr[second] = temp;
}

function choosePivot(arr, left, right) {
  return left;
}

var sample = [9,8,7,6,5,4,3,2,1];
console.log(quicksort(sample, 0, sample.length-1));
