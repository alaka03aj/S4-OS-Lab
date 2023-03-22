echo "Enter number 1"
read a
echo "Enter number 2"
read b

echo "Before swapping: $a, $b"

temp=$a
a=$b
b=$temp

echo "After swapping: $a, $b"
