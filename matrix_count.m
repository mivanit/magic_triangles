function matrix_count(v)
% matrix_count

% mod number
mnum = 3;
% summary output filename
fname = 'summary.csv';
sumout = fopen(fname,'w');

% write header
header = 'n,total';
for n = v
    header = [header ',' num2str(n)];
end
fprintf(sumout,[header '\n']);

% go through each element of inputted vector and run count(n) on it
for i = 1:length(v)
    % get n
    n = v(i);
    tic
    % get counts
    counts = count(n,mnum);
    toc
    % write out to summary file
    fprintf(sumout,'%d,',n);
    fprintf(sumout,[repmat('%d,',[1 n])],counts);
    fprintf(sumout,'\n');
end
% close file
fclose(sumout);
fclose all;
disp('Done');
end

function counts = count(n,mnum)
% count number of good matrices in n triangle

% output file name
fname = ['n_' num2str(n) '.txt'];
fname_csv = ['n_' num2str(n) '.csv'];

if n <= 0
    disp('ERROR: n must be positive integer')
    exit 1
end
% input is positive
% output file
outfile = fopen(fname, 'wt');
outcsvfile = fopen(fname_csv, 'w');
fprintf(outfile, ['Analyzing ' num2str(floor(n)) ' triangle :\n']);
fprintf(outfile,'\n');

% number of cards in triangle
ncards = nchoosek(n+1, 2);
% all permutations of first n cards
perms = nchoosek(1:ncards, n);
% total number of permutations
nperms = length(perms);

% write numberes to output file
fprintf(outfile,['Number of cards = ' num2str(ncards) '\n']);
fprintf(outcsvfile,['Number of permutations:,' num2str(nperms) '\n']);
fprintf(outfile,'\n');
fprintf(outcsvfile,'\n');

% initialize M (matrix of values in terms of first row numbers)
M = zeros([ncards, n]);
az = 0;
% go through each row and print out triangle, labeled 1-ncards
for r = 1:n
    curr_row = '';
    curr_row_csv = '';
    % label each position with a number
    for c = 1:(n-r+1)
        az = az+1;
        curr_row = [curr_row ' ' num2str(az)];
        curr_row_csv = [curr_row_csv ',' num2str(az)];
    end
    % write out triangle to file
    fprintf(outfile,[curr_row '\n']);
    fprintf(outcsvfile,[curr_row_csv '\n']);
    % set first n rows diagonals to 1
    M(r,r) = 1;
end

fprintf(outfile,'\n');
fprintf(outcsvfile,'\n');

for i = 2:n
    offset = 0;
    for k = 1:(i-1)
        offset = offset + (n-(k-1));
    end
    rvoffset = 0;
    if i > 2
        for k = 1:(i-2) 
            rvoffset = rvoffset + (n-(k-1));
        end
    end
    for j = 1:(n-i+1)
        r = offset + j;
        rv1 = j + rvoffset;
        rv2 = rv1 + 1;
        v1=M(rv1,:);
        v2=M(rv2,:);
        value = mod(2*(v1+v2),mnum);
        M(r,:) = value;
    end
end

for i = 1:ncards
    v = M(i,:);
    fprintf(outfile,[repmat('%5d ',[1,n]) '\n'],v);
    fprintf(outcsvfile,[repmat(',%5d',[1,n]) '\n'],v);
end
disp(M);

counts=zeros([1 n+1]);
for p = 1:nperms
    perm = perms(p,:);
    matrix = NaN(n);
    for i = 1:n
        v = M(perm(i),:);
        matrix(i,:) = v(:);
    end
    
    if modrank(matrix,mnum) < n
        fprintf(outfile,['\nNo: ']);
        fprintf(outcsvfile,['\nNo,']);
        fprintf(outfile,repmat('%5d ',[1,n]),perm);
        fprintf(outcsvfile,repmat('%5d,',[1,n]),perm);
    else
        fprintf(outfile,'\nYes:');
        fprintf(outcsvfile,['\nYes,']);
        fprintf(outfile,repmat('%5d ',[1,n]),perm);
        fprintf(outcsvfile,repmat('%5d,',[1,n]),perm);
        counts(1)=counts(1)+1;
        nfirstrow = 0;
        for i = 1:n
            if any(i==perm)
                nfirstrow = nfirstrow + 1;
            end
        end
        counts(nfirstrow + 1) = counts(nfirstrow+1) + 1;
    end
end
fprintf(outfile,'\n');
fprintf(outcsvfile,'\n');
fprintf(outfile,['\nTotal invertible permutations: ' num2str(counts(1)) '/' num2str(nperms) '\n\n']);
fprintf(outcsvfile,['\nTotal invertible permutations,' num2str(counts(1)) ',' num2str(nperms) '\n\n']);
fprintf(outfile,'Number of invertible permutations with __ number of cards in the first row:\n');
fprintf(outcsvfile,'Number of invertible permutations with __ number of cards in the first row:\n');
for i = 1:n
    fprintf(outfile,[num2str(i) ': ' num2str(counts(i+1)) '\n']);
    fprintf(outcsvfile,[num2str(i) ',' num2str(counts(i+1)) '\n']);
end
fclose(outfile);
end


function R = modrank(A,p)
% modrank: compute the rank of an integer array, modulo p
% usage: R = modrank(A,p)
%
% Returns the rank of the matrix A under
% modulo arithmetic, mod p.
% 
% Because all operations are performed using
% integer arithmetic, the computed rank will
% be exact.
%
% Arguments: (input)
%  A - A must be a 2-d array of integer
%      elements, or any vpi array.
%
%  p - any scalar integer or vpi number
%      Required: p > 1
%
%      If p > sqrt(2^53-1), then computations
%      will be done in a vpi form, which will
%      be somewhat slower than otherwise.
% 
% Arguments: (output)
%  R - an integer that denotes the rank of A
%
%        0 <= R <= min(size(A))
%
% Example: 
%  A = magic(5)
% A =
%    17    24     1     8    15
%    23     5     7    14    16
%     4     6    13    20    22
%    10    12    19    21     3
%    11    18    25     2     9
%
% modrank(A,2)
% ans =
%      4
%
% modrank(A,5)
% ans =
%      2
%
% modrank(A,29)
% ans =
%      5
%
%  See also: rank, mod, rem
%  
% 
%  Author: John D'Errico
%  e-mail: woodchips@rochester.rr.com
%  Release: 1.0
%  Release date: 3/3/09

if (nargin~=2)
  error('Exactly two arguments required for modrank')
end

if (numel(p) ~= 1) || (p <= 1)
  error('p must be scalar numeric or scalar vpi, p > 1')
end

% an empty matrix must have rank 0
if isempty(A) || isempty(p) || (p == 1)
  R = 0;
  return
end

% get the shape of A
sa = size(A);
if length(sa) > 2
  error('A may not be more than a 2 dimensional array')
end
nr = sa(1);
nc = sa(2);

if (~isnumeric(A) && ~isa(A,'vpi')) || (isnumeric(A) && all((A(:)~=round(A(:)))))
  error('A must be an integer numeric array or a vpi array')
end

% if A has more rows than columns, best to transpose.
% this will not change the rank.
if (nr > nc)
  A = A.';
  [nr,nc] = deal(nc,nr);
end

% p mst be limited to sqrt(2^53 - 1), or else we must
% convert to vpi arithmetic
if p > sqrt(2^53-1)
  A = vpi(A);
end

% take the mod first, just in case
A = mod(A,p);

% do the work here. this will just be gaussian
% elimination, with column and row pivoting in
% case of zero pivots
i = 1;
R = nr; % in case we drop through the while loop
flag = true;
while flag && (i<=nr)
  % choose a pivot element
  [ipiv,jpiv] = find(A(i:nr,i:nc),1,'first');
  if isempty(ipiv)
    % the rank has been revealed if no
    % non-zeros remain for pivoting
    R = i-1;
    break
  end
  if i > 1
    ipiv = ipiv + i-1;
    jpiv = jpiv + i-1;
  end

  % swap rows
  if ipiv ~= i
    A([ipiv,i],:) = A([i,ipiv],:);
  end
  % and columns
  if jpiv ~= i
    A(:,[jpiv,i],:) = A(:,[i,jpiv]);
  end
  
  % kill off the remaining elements in the i'th column
  % if i == nr, then we are done, since A(i,i) must be
  % non-zero since we just did a pivot op.
  if i < nr
    % the pivot element
    piv = A(i,i);
    
    % which elements of A below the pivot are non-zero?
    k = i + find(A((i+1):nr,i));
    if ~isempty(k)
      for m = 1:length(k)
        A(k(m),(i+1):nc) = mod(piv*A(k(m),(i+1):nc) - A(k(m),i)*A(i,(i+1):nc),p);
        A(k(m),i) = 0;
      end
    end
  end
  
  % increment i to keep working
  i = i + 1;
end
end
