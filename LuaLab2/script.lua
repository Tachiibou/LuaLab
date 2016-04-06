function sqr(rot)
	return rot*rot
end

function sqr2(rot)
	return rot*rot*rot
end

function fibbonacci(tal)
if tal <= 2 
then return 1 
else return(fibbonacci(tal-2) + fibbonacci(tal-1)) end
end