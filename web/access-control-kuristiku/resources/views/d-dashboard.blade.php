@extends('layouts.dashboard')

@section('sidebar')
	@parent

	<li>
		<a href="{{ url('/') }}"><i class="fa fa-dashboard fa-fw"></i> Dashboard</a>
	</li>
@endsection

@section('contentTitle', 'Dashboard')

@section('content')

@endsection