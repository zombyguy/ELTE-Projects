#=
A program nincs kész, valahol logikai hiba található a leghosszabb antilánc kiszámításában.
=#

using Primes

function main()
    limit::UInt = parse(UInt, readline())

    known_sizes::Dict{Vector{UInt8}, UInt} = Dict()

    result::UInt = 1 # manually add 1
    for i in 2:limit
        sizes::Vector{UInt8} = get_sizes_from_factors(i)
        result += calculate_max_antichain(sizes, Ref(known_sizes))
    end
    println(result)
end

function get_sizes_from_factors(n::UInt)::Vector{UInt8}
    factors = collect(factor(n))
    exponents::Vector{UInt8} = []
    for factor in factors
        append!(exponents, factor[2]+1) # +1 because of triangle sizes
    end
    sort!(exponents, rev=true)
    return exponents
end

function calculate_max_antichain(sizes::Vector{UInt8}, _known_sizes::Base.RefValue{Dict{Vector{UInt8}, UInt}})::UInt
    if length(sizes) <= 1
        return 1
    end

    return get_cut_triangle_volume(UInt(length(sizes)), sizes, _known_sizes)

end 

function get_cut_triangle_volume(dim::UInt, sizes::Vector{UInt8}, _known_sizes::Base.RefValue{Dict{Vector{UInt8}, UInt}})::UInt
    if sizes in keys(_known_sizes[])
        return _known_sizes[][sizes]
    end
    
    volume = calculate_triangle_volume(dim-1, sizes[1])
    for i in 2:dim
        if sizes[1] == sizes[i] # ha nincs mit levágni
            continue
        end 

        temp_sizes::Vector{UInt8} = fill(sizes[1] - sizes[i], dim) ## valószínű itt a hiba
        for j in 2:(i-1)
            if sizes[j] < sizes[i] # lehet át lehe írni egyszerűbbre
                temp_sizes[j] = sizes[j] - sizes[1] # nem tudom miért, de működik
            end
        end
        sort!(temp_sizes, rev=true)
        volume -= get_cut_triangle_volume(dim, temp_sizes, _known_sizes)
    end

    _known_sizes[][sizes] = volume
    return volume
    
end

function calculate_triangle_volume(dim, side_length)
    # implement dynamic programming to speed up
    if dim == 1
        return side_length
    end

    if side_length == 1
        return 1
    end

    volume = calculate_triangle_volume(dim-1, side_length)
    volume += calculate_triangle_volume(dim, side_length-1)
    return volume
end

main()