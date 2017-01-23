@extends('layouts.dashboard')

@section('contentTitle', 'Cards')

@push('scripts')
	<!-- DataTables JavaScript -->
	<script src="/vendor/datatables/js/jquery.dataTables.min.js"></script>
	<script src="/vendor/datatables-plugins/dataTables.bootstrap.min.js"></script>
	<script src="/vendor/datatables-responsive/dataTables.responsive.js"></script>

	<!-- Tables -->
    <script>
    $(document).ready(function() {
        $('#dataTables').DataTable({
            responsive: true
        });
    });
    </script>
@endpush

@section('content')
<div class="row">
	<div class="col-lg-3 col-md-6">
		<div class="panel panel-default">
			<div class="panel-heading">
				Import Cards
			</div>
			<div class="panel-body">
			    
			</div>
		</div>
	</div>
	<div class="col-lg-9">
        <div class="panel panel-default">
            <div class="panel-heading">
                Active cards
            </div>
            <!-- /.panel-heading -->
            <div class="panel-body" style="padding-bottom: 0px;">
                <table width="100%" class="table table-striped table-bordered table-hover" id="dataTables">
                    <thead>
                        <tr>
                            <th>UID</th>
                            <th>ISIC ID</th>
                        </tr>
                    </thead>
                    <tbody>
	                    @foreach ($cards as $card)
	                        <tr>
	                            <td>{{ $card -> cardUID }}</td>
	                            <td>{{ $card -> isicID }}</td>
	                       	</tr>
	                    @endforeach
                    </tbody>
                </table>
            </div>
        </div>
    </div>
</div>
@endsection